import socket
import sys

port_r = 8084
port_s = 2001
IP = '192.168.3.1'


try:

	rec = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	print("Socket Created")

	# Bind the Socket
	rec.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	rec.bind(('', port_r))
	print("ServerBinded @port: ", port_r)

	# Put Socket into listening mode
	rec.listen(5)

	c, addr = rec.accept()
	print (addr, " Connected")
	
	hotspot = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	hotspot.connect((IP, port_s))

	while True:
		data = c.recv(1024)
		print(data)
		if data:
			hotspot.send(data)
			print("Sent..")
		else:
			print("Disconnected...")
			# Stop the robot in case of connection lost
			hotspot.send(b"\xFF\x00\x00\x00\xFF")
			c, addr = rec.accept()
			print (addr, " Connected")


		
except KeyboardInterrupt:
	sys.exit(0)
		
