#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

// Set the wifi connection
char ssid[] = "";
char psswd[]="";

String host = "";  			//raspberry ip

int hostport = 8081;                          	

byte myByte[10];
char myFloat[50] = "";
bool dataReceived = false;
float f;

SoftwareSerial mySerial(13, 15); //D7rx, D8tx
WiFiClient wifi;

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(9600);
  mySerial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, psswd);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(500);
}

void loop() {
  
  receiveByte();
  makeString();

}

void receiveByte() {
  int i = 0;

  while (mySerial.available()) {
    myByte[i] = mySerial.read();  //gets one byte from serial buffer
    i++;
    if (i == 4) {

      f = *((float*)(myByte));
      i = 0;
    }
    dataReceived = true;
    if (mySerial.available() < 1) {
      delayMicroseconds(200);  //delay to allow buffer to fill
    }
  }
}


void makeString() {
  if (dataReceived) {
    
    sprintf(myFloat, "%f", f);
    Serial.print("myFloat: ");
    Serial.println(myFloat);
    dataReceived = false;
    connectToSocket(myFloat);
  }
}


void connectToSocket(String data) {

  if (!wifi.connect(host, hostport)) {
    Serial.println("connection failed");
    //return;
  }
  else {
    Serial.println("Sending to SKT");
    wifi.print(data);
  }
}
