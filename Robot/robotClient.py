import cv2
import urllib.request
import numpy as np
import sys
import pygame
import threading
import os
import socket
import time

# Print into pygame screen
def printMsg(pos, message):
    txtSurface = myFont.render(message, False, (255,255,255))
    screen.blit(txtSurface, pos)
    pygame.display.flip()

# Pigame init
size = (w, h) = (640, 640)
status = (150, 500)

pygame.init()
pygame.font.init()
screen = pygame.display.set_mode(size)
pygame.display.set_caption("Robot Stream Client")
myFont = pygame.font.SysFont("timesi", 21)
rect = pygame.Rect(150, 500, 400, 29)

printMsg((200, 300), "Chose local [L] or Remote [R]")


# Check if you we are in local connection
not_valid = True
while not_valid:
	for event in pygame.event.get():

		if event.type == pygame.QUIT:
					print("bye...")
					os._exit(1) 

		if event.type == pygame.KEYDOWN:

			if event.key == pygame.K_l:
				local = 1
				not_valid = False
			if event.key == pygame.K_r:
				local = 0
				not_valid = False

printMsg((15, 500), "STATUS:")
printMsg((15, 530), "COMMANDS:")
printMsg((15, 560), "MOVE:                      W,A,S,D")
printMsg((15, 590), "CHANGE SPEED:     M: High, N: Medium, B: Low")


############################################################################################
#       Communication with Raspy
############################################################################################

def connectToMotion():

	screen.fill((0,0,0), rect)
	printMsg(status, "Disconnected From Motion Server")

	not_connected = True
	while not_connected:

		for event in pygame.event.get():

			if event.type == pygame.QUIT:
						print("bye...")
						os._exit(1)

		if local == 1:
			url = 'http://192.168.3.50:8085/frame.mjpg'
		else:
			url = 'http://192.168.1.198:8085/frame.mjpg'

		try:
		    # Connect to motion server
		    stream = urllib.request.urlopen(url)
		    print("Connected to motion Server")
		    screen.fill((0,0,0), rect)
		    printMsg(status, "Connected")
		    not_connected = False
		except Exception:
		    print("Waiting for motion Server...")
		    screen.fill((0,0,0), rect)
		    printMsg(status, "Waiting for motion Server...")
		    time.sleep(1)
		    pass

	return stream



########################################################################
#       Thread used to take imput from keyboard
########################################################################

def th_pygameKey():

	# Directions
	FORWARD     		= b"\xFF\x00\x02\x00\xFF"
	BACKWARD    		= b"\xFF\x00\x01\x00\xFF"
	LEFT        		= b"\xFF\x00\x03\x00\xFF"
	RIGHT       		= b"\xFF\x00\x04\x00\xFF"
	STOP       	 		= b"\xFF\x00\x00\x00\xFF"

	# Speed
	LOW_SPEED_L 		= b"\xFF\x02\x02\x02\xFF"
	LOW_SPEED_R 		= b"\xFF\x02\x01\x02\xFF"
	MED_SPEED_L 		= b"\xFF\x02\x02\x0A\xFF"
	MED_SPEED_R 		= b"\xFF\x02\x01\x0A\xFF"
	HIGH_SPEED_L 		= b"\xFF\x02\x02\x5A\xFF"
	HIGH_SPEED_R 		= b"\xFF\x02\x01\x5A\xFF"

	# Camera	
	ZERO_BASE 				= 80
	ZERO_POSITION_BASE		= str('{:02x}'.format(ZERO_BASE))

	ZERO_CAMERA 			= 40
	ZERO_POSITION_CAMERA	= str('{:02x}'.format(ZERO_CAMERA))

	SERVO_BASE			= "FF0107%sFF" 
	SERVO_CAMERA		= "FF0108%sFF"


	MAX_ANGLE			= 160
	MIN_ANGLE			= 40

	global tmp_base_angle 
	global tmp_camera_angle 

	tmp_base_angle = ZERO_BASE 
	tmp_camera_angle = ZERO_CAMERA

	run_forward = False
	run_backward = False
	run_left = False
	run_right = False


###########################################################################################
#			Send Commands To Raspy
###########################################################################################

	def connectToRobot():

		screen.fill((0,0,0), rect)
		printMsg(status, "Disconnected From Robot Server")

		if local == 0:
			# Raspberry pi
			IP = '192.168.1.198'
		else:
			# Local connection
			IP = '192.168.3.50'

		PORT = 8084

		# Init the socket
		s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

		not_connected = True
		while not_connected:
		    try:
		        s.connect((IP, PORT))
		        not_connected = False
		        print("Connected to Robot Server")
		        screen.fill((0,0,0), rect)
		        printMsg(status, "Connected")

		    except Exception:
		        print("Waiting for Robot server...")
		        screen.fill((0,0,0), rect)
		        printMsg(status, "Waiting for Robot Server...")
		        time.sleep(1)
		        pass

		return s

	def sendForward(socket):
	    print("FORWARD")
	    socket.send(FORWARD)

	def sendBackward(socket):
	    print("BACKWARD")
	    socket.send(BACKWARD)

	def sendLeft(socket):
	    print("LEFT")
	    socket.send(LEFT)

	def sendRight(socket):
	    print("RIGHT")
	    socket.send(RIGHT)

	def sendStop(socket):
	    print("Stop")
	    socket.send(STOP)

	def keyUp(socket):
		if run_forward:
			sendForward(socket)
		elif run_backward:
			sendBackward(socket)
		elif run_left:
			sendLeft(socket)
		elif run_right:
			sendRight(socket)
		else:
			sendStop(socket)

	def setSpeedLow(socket):
	    print("Speed Setted to: LOW")
	    socket.send(LOW_SPEED_L)
	    socket.send(LOW_SPEED_R)

	def setSpeedMed(socket):
	    print("Speed Setted to: MED")
	    socket.send(MED_SPEED_L)
	    socket.send(MED_SPEED_R)

	def setSpeedHigh(socket):
	    print("Speed Setted to: HIGH")
	    socket.send(HIGH_SPEED_L)
	    socket.send(HIGH_SPEED_R)

	def resetCamera(socket):
		print("Camera in Home position")
		cmd_base = bytes.fromhex(SERVO_BASE % ZERO_POSITION_BASE)
		cmd_camera = bytes.fromhex(SERVO_CAMERA % ZERO_POSITION_CAMERA)
		socket.send(cmd_base)
		socket.send(cmd_camera)
		global tmp_base_angle
		global tmp_camera_angle 
		tmp_base_angle = ZERO_BASE
		tmp_camera_angle = ZERO_CAMERA
		

	def cameraRight(socket):
		print("Turn camera RIGHT")
		global tmp_base_angle 
		if tmp_base_angle > MIN_ANGLE:
			tmp_base_angle -= 2
			angle = '{:02x}'.format(tmp_base_angle)
			cmd = bytes.fromhex(SERVO_BASE % angle)
			socket.send(cmd)

	def cameraLeft(socket):
		print("Turn camera LEFT")
		global tmp_base_angle 
		if tmp_base_angle < MAX_ANGLE:
			tmp_base_angle += 2
			angle = '{:02x}'.format(tmp_base_angle)
			cmd = bytes.fromhex(SERVO_BASE % angle)
			socket.send(cmd)

	def cameraUp(socket):
		print("Turn camera UP")
		global tmp_camera_angle 
		if tmp_camera_angle < (MAX_ANGLE-ZERO_CAMERA):
			tmp_camera_angle += 2
			angle = '{:02x}'.format(tmp_camera_angle)
			cmd = bytes.fromhex(SERVO_CAMERA % angle)
			socket.send(cmd)

	def cameraDown(socket):
		print("Turn camera Down")
		global tmp_camera_angle 
		if tmp_camera_angle > (MIN_ANGLE-ZERO_CAMERA):
			tmp_camera_angle -= 2
			angle = '{:02x}'.format(tmp_camera_angle)
			cmd = bytes.fromhex(SERVO_CAMERA % angle)
			socket.send(cmd)

	print("Thread Created")

	s = connectToRobot()  

	while True:

		try:

			for event in pygame.event.get():

				if event.type == pygame.QUIT:
					print("bye...")
					os._exit(1) 

				if event.type == pygame.KEYDOWN:

					if event.key == pygame.K_w:
						run_forward = True
						sendForward(s)
					                
					if event.key == pygame.K_s:
						run_backward = True
						sendBackward(s)

					if event.key == pygame.K_a:
						run_left = True
						sendLeft(s)

					if event.key == pygame.K_d:
						run_right = True
						sendRight(s)

					if event.key == pygame.K_b:
						setSpeedLow(s)

					if event.key == pygame.K_n:
						setSpeedMed(s)

					if event.key == pygame.K_m:
						setSpeedHigh(s)

					if event.key == pygame.K_SPACE:
						resetCamera(s)

					if event.key == pygame.K_UP:
						cameraUp(s)

					if event.key == pygame.K_DOWN:
						cameraDown(s)

					if event.key == pygame.K_LEFT:
						cameraLeft(s)

					if event.key == pygame.K_RIGHT:
						cameraRight(s)

				if event.type == pygame.KEYUP:

					if event.key == pygame.K_w:
						run_forward = False
						keyUp(s)
        
					if event.key == pygame.K_s:
						run_backward= False
						keyUp(s)

					if event.key == pygame.K_a:
						run_left = False
						keyUp(s)

					if event.key == pygame.K_d:
						run_right = False
						keyUp(s)


		except socket.error as e:
			print(e)
			s.close()
			s = connectToRobot()
			pass



	return



################################################################################
#       "main"
################################################################################

try:

	stream = connectToMotion()
	t = threading.Thread(target=th_pygameKey)
	t.start()

	bytes = bytes()

	while True:

		try:

			while True:
	    		# Read Data From motion server
				bytes += stream.read(1024)
				a = bytes.find(b'\xff\xd8')
				b = bytes.find(b'\xff\xd9')
				if a != -1 and b != -1:
					jpg = bytes[a:b+2]
					bytes = bytes[b+2:]
	
	    			# Convert and print the image received
					i = cv2.imdecode(np.frombuffer(jpg, dtype=np.uint8), cv2.COLOR_BGR2RGB)
					i = cv2.cvtColor(i, cv2.COLOR_BGR2RGB)
					image = pygame.surfarray.make_surface(i)
					#image = pygame.transform.rotate(image, 270)
					image = pygame.transform.flip(image, 1, 0)
					screen.blit(image, (0,0))
					pygame.display.flip()

		except Exception:
			stream = connectToMotion()
			print("Connessione ristabilita")
			pass


    

except KeyboardInterrupt :
    print("Bye...")
    os._exit(1)

################################################################################
