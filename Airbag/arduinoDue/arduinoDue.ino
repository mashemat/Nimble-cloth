#include<Wire.h>
#include<DueTimer.h>
#include "globals.h"

void takeReading() ;
void turnOff();

void setup() {

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, HIGH);
  delay(500);
  pinMode(VALVE, OUTPUT);
  digitalWrite(VALVE, LOW);

  Wire.begin();
  Wire.beginTransmission(SENSOR);
  Wire.write(0x6B);                 // PWR_MGMT_1 register
  Wire.write(0);                    // set to zero (wakes up the sensor-6050)
  Wire.endTransmission(true);

  Serial.begin(115200);
  Serial1.begin(115200);

  if (DEBUG)
    Serial.print("**********************  Welcome   ***************************** \n");

  Timer1.attachInterrupt(takeReading);
  Timer1.start(TIME_TO_WAIT_1);
  Timer2.start(1000000);
  Timer2.attachInterrupt(turnOff);

  changeState(0);

}

void loop() {
  if (compute_flag) {

    compute_flag = false;

    float tmp_yy = readVector[0];

    predictValue = predict();

    ErrNorm = computeErrNorm();

    //send data to esp8266
    tx((float)predictValue, (float)readVector[0], (float)ErrNorm);


    if (DEBUG) {
      Serial.println("\nPredicted\tReal");
      Serial.print(predictValue);
      Serial.print("\t\t");
      Serial.print(readVector[0]);
      Serial.println("\n");
    }


    if (ErrNorm > THRESHOLD) {

      if (DEBUG){
        Serial.print("STATE 1->>>  ");
        Serial.println(yy);
        
      }
      changeState(1);
      
      if (yy < FALL_THRESHOLD) {
        float gyr_res = sqrt(pow(GyrXX, 2) + pow(GyrZZ, 2));
        Serial.print("gyr_res"); Serial.println(gyr_res);
      	if(gyr_res > GYR_THRESHOLD)
        	changeState(2);

      }

      else {
        changeState(0);
        if (DEBUG)
          Serial.println("STATE 0");
      }


      if (DEBUG) {
        Serial.println("\n\n*********************************************************************");
      }

    }
    else {
         if (DEBUG)
          Serial.println("STATE 0");
          changeState(0);
      }

  }
}


//ISR on timer1
void takeReading() {

  shiftVectorUp((float *)readVector);
  readVector[0] = normalizedAcquisition();
  readsCount ++;

  if (readsCount > 3) {
    compute_flag = true;
    readsCount = 0;
  }
}

void turnOff(){
  digitalWrite(BLUE, LOW);
  Serial.println("----------------------------------------------TURNDOWN");
}
