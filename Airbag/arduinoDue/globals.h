#ifndef globals_h
#define globals_h

#define DEBUG 1 

#define TIME_TO_WAIT_1    10000 //us

#define RED               13
#define GREEN             11
#define BLUE              8//12
#define READS             10
#define SENSOR            0x68
#define ACL_OFFSET        16384.0
#define GYR_OFFSET        131.0
#define THRESHOLD         5.0
#define FALL_THRESHOLD    1.0
#define GYR_THRESHOLD     1700.0
#define INFLATE_TIME      1000 
#define VALVE             9

int toggle = 1;
int normal_walk = 0; // State 1
int check_abnormal = 0; // State 2
int inflate = 0; // State 3

volatile int readsCount = 0;
  
volatile float xx;
volatile float yy;
volatile float zz;

volatile float GyrXX;
volatile float GyrYY;
volatile float GyrZZ;

float prediction;
float ErrNorm;
int indx = 4;
int predictCount = 0;
int realIndex = 0;

float readVector[4];
float predictValue;

volatile bool compute_flag = false;
volatile bool first_time = true;

float a1[12][3] = { { -0.0369991024386149, -0.244031651824727,  0.0144650909251497},
  {0.543520737916964,  -1.89368915085994, 1.74207336762423},
  { -0.585895915460979, 1.78230330922965,  -0.569849146544807},
  { -34.2841001395290,  37.5993671033386,  -27.7032639761990},
  { -2.25209218585098,  4.18207314101617,  -4.81283280048628},
  {1.06899089309827, -1.61939236612749, 1.10450198220137},
  {0.526952515943491, -0.412477388776106,  0.00654194954497747},
  { -2.01396498503777, 0.731449590550159, 2.82490722678340},
  {2.21440914698219,  -4.13382465483222, 4.75750461615940},
  {0.209901724583300, -0.636896785787971,  0.281154683783578},
  {0.263158965449764, -0.192101322902902,  0.257505711877490},
  {0.354586963408479, -0.766733638076839,  0.356199019034204}
};


float b1[12][1] = { {3.29950172553891},
  { -5.01934146768881},
  { -6.02835135899091},
  {249.508938468682},
  {28.1416137739969},
  { -6.08042026100091},
  { -1.46348611737855},
  { -14.8087530559878},
  { -27.7148524015725},
  { -0.293567751186886},
  { -3.74762155870178},
  {0.300957437836779}
};

float a2[12] = { -10.2431766897031,  -0.537374158102275,  1.01667664521121,  0.0756292952763091,  9.63186555784810,  1.70505930617385,  1.96068271970690,  -0.0997689576769086, 9.77551258504664,  -20.8162467997348, -8.13937909801326, 7.04792448705510};
float b2 = -4.89317692518856;


float normalizedAcquisition()
{
  Wire.beginTransmission(SENSOR);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(SENSOR, 14, true); // request a total of 14 registers

  int16_t AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  int16_t AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  int16_t AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  int16_t Temp = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  int16_t GyrX = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  int16_t GyrY = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  int16_t GyrZ = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)

  xx = (AcX * 10) / ACL_OFFSET;
  yy = (AcY * 10) / ACL_OFFSET;
  zz = (AcZ * 10) / ACL_OFFSET;

  GyrXX = (GyrX * 10) / GYR_OFFSET;
  GyrYY = (GyrY * 10) / GYR_OFFSET;
  GyrZZ = (GyrZ * 10) / GYR_OFFSET;

  //  if (DEBUG) {
  //    Serial.print("xx:\t"); Serial.print(xx); Serial.print("\t");
  //    Serial.print("yy:\t"); Serial.print(yy); Serial.print("\t");
  //    Serial.print("zz:\t"); Serial.println(zz);
  //  }


  return sqrt(pow((xx),2) + pow((yy), 2) + pow((zz), 2));
  //return yy;
}

void printVector(float * v, int s) {
  if (DEBUG)
    Serial.print("printVector\t\t");
  for (int i = 0; i < s; i++) {
    Serial.print(v[i]); Serial.print(" ");
  }
  Serial.println("");
}


void printRead(float * v) {
  if (DEBUG)
    Serial.print("printRead\t\t");
  for (int i = 0; i < 4; i++) {
    Serial.print(v[i]); Serial.print(" ");
  }
  Serial.println("");
}

float square(float x) {
  return pow(x, 2);
}

void MMultiply(float * A, float * B, int m, int p, int n, float * C)
{
  // A = input matrix (m x p)
  // B = input matrix (p x n)
  // m = number of rows in A
  // p = number of columns in A = number of rows in B
  // n = number of columns in B
  // C = output matrix = A*B (m x n)
  int i, j, k;
  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++)
    {
      C[n * i + j] = 0;
      for (k = 0; k < p; k++)
        C[n * i + j] = C[n * i + j] + A[p * i + k] * B[n * k + j];
    }
}

//Matrix Addition Routine
void MAdd(float * A, float * B, int m, int n, float * C)
{
  // A = input matrix (m x n)
  // B = input matrix (m x n)
  // m = number of rows in A = number of rows in B
  // n = number of columns in A = number of columns in B
  // C = output matrix = A+B (m x n)
  int i, j;
  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++)
      C[n * i + j] = A[n * i + j] + B[n * i + j];
}

float predict()
{
  float result1[13];
  float result2[13];
  float result3[13];
  float result4;


//  if (DEBUG) {
//      Serial.print("MMultiply\t");
//      printVector((float *)readVector, 4);
//    }
//
//     if (DEBUG) {
//      Serial.print("readvectore +1\t");
//      printVector((float *)readVector +1, 3);
//    }
//
//      if (DEBUG) {
//      Serial.print("MMultiply\t");
//      printVector((float *)readVector, 4);
//    }
    
  MMultiply((float*)a1, (float*)readVector + 1, 13, 3, 1, (float*)result1);
   
  MAdd((float*)result1, (float*)b1, 13, 1, (float*)result2);
  for (int j = 0; j < 13; j++)
  {
    result3[j] = tanh(result2[j]);
  }
  MMultiply((float*)a2, (float*)result3, 1, 13, 1, &result4);

  if (DEBUG) {
    Serial.print("predict: ");
    Serial.println(result4 + b2);
  }


  return (result4 + b2);

}

float computeErrNorm()
{
  ErrNorm = abs(predictValue - readVector[0]);

  if (DEBUG) {
    Serial.print("Value of ErrNorm is  ");
    Serial.println(ErrNorm);
  }

  return ErrNorm;
}

float tanh(float x)
{
  if (x > 50.50)
    return 1;
  else if (x < -50.50)
    return -1;
  else {
    float x0 = exp(x);
    float x1 = 1.0 / x0;

    return ((x0 - x1) / (x0 + x1));
  }
}

void shiftVectorDown( float * vector) {
  int i;
  for (i = 1; i < 5; i++) {
    vector[i - 1] = vector[i];
  }
  vector[4] = 0;
}

void shiftVectorUp( float * vector) {
  int i;
  float tmp, tmp_old = vector[0];
  for (i = 0; i < 4; i++) {
    tmp = vector[i];
    vector[i] = tmp_old;
    tmp_old = tmp;
  }
  vector[0] = 0;
}



void sendFloatByte(float numberToSend) {
  byte *b = (byte*)&numberToSend;

  Serial1.write(b[0]);
  Serial1.write(b[1]);
  Serial1.write(b[2]);
  Serial1.write(b[3]);
}

void tx(float pred, float real, float fit) {

  sendFloatByte(pred);
  sendFloatByte(real);
  sendFloatByte(fit);

  if (DEBUG) {
    Serial.print("tx\t");
    Serial.print(pred);
    Serial.print(" ");
    Serial.print(real);
    Serial.print(" ");
    Serial.println(fit);
  }

}

void inflateAirbag () {
    Timer1.detachInterrupt();
    long int timestart = millis();
    digitalWrite(VALVE, HIGH);
    while((millis()-timestart)<INFLATE_TIME);
    digitalWrite(VALVE, LOW);
    //Serial.println("YOU ARE STILL ALIVE, maybe");
  }
  
void changeState(int s){

  switch(s){
    case 0:
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
      //digitalWrite(BLUE, LOW);
      break;
    case 1:
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, LOW);
      toggle=1^toggle;
      digitalWrite(BLUE, HIGH);
      //Timer2.start(1000000);
      //Timer2.stop();
      //delay(500);
      break;
    case 2:
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, LOW);
      //digitalWrite(BLUE, LOW);
      inflateAirbag();
      Timer1.stop();
      compute_flag = false;
      break;
  }
    
      
}



#endif
