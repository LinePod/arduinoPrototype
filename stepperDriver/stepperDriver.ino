#include <Wire.h>
// Arduino Nano as Stepper Driver
// Input: (x,y) vector as absolute value
// Output: Done

// Stepper Horizontal
const int ENA_HZ = 7;
const int IN1_HZ = 6;
const int IN2_HZ = 5;
const int ENB_HZ = 8;
const int IN4_HZ = 9;
const int IN3_HZ = 10;

// Stepper Vertical
const int ENA_VT = 2;
const int IN1_VT = 3;
const int IN2_VT = 4;
const int ENB_VT = 13;
const int IN4_VT = 12;
const int IN3_VT = 11;

const int readyPin = 1;

int stepperState[2] = {0,0};
int x;
int y;
int go = 0;

void setup()
{
  pinMode(ENA_HZ,OUTPUT);
  pinMode(IN1_HZ,OUTPUT);
  pinMode(IN2_HZ,OUTPUT);
  pinMode(ENB_HZ,OUTPUT);
  pinMode(IN3_HZ,OUTPUT);
  pinMode(IN4_HZ,OUTPUT);
  pinMode(ENA_VT,OUTPUT);
  pinMode(IN1_VT,OUTPUT);
  pinMode(IN2_VT,OUTPUT);
  pinMode(ENB_VT,OUTPUT);
  pinMode(IN3_VT,OUTPUT);
  pinMode(IN4_VT,OUTPUT);
  pinMode(readyPin, OUTPUT);
  digitalWrite(ENA_HZ, HIGH);
  digitalWrite(ENB_HZ, HIGH);
  digitalWrite(ENA_VT, HIGH);
  digitalWrite(ENB_VT, HIGH);

  digitalWrite(readyPin, HIGH); 
  Wire.begin(1);
  Wire.onReceive(receiveEvent);
}

void loop() {
  if(go == 1) {
    digitalWrite(readyPin, LOW);
    drive(x,y);
    digitalWrite(readyPin, HIGH); 
    go = 0;
  }
  delay(500);
}

void receiveEvent(int bytes) {
  digitalWrite(readyPin, LOW);
  char c;
  x = Wire.read();// - 127;
  y = Wire.read();// - 127;
  go = 1;
  c = Wire.read();
}

void drive(int x, int y) {
  for(int i=0; i < 100;++i) {
    forward(1,120,0);
    forward(1,120,1);
  }
  /*if(x>0) {
    forward(x,20,0);
  }
  else if(x<0) {
    reverse(x,20,0);
  }

  if(y>0) {
    forward(y,20,1);
  }
  else if(y<0) {
    reverse(y,20,1);
  }
  */
}

void setState(int state, int motor) {
  if(motor == 0) {

    switch(state) {
      case 0:
          digitalWrite(IN1_HZ, 0);
          digitalWrite(IN2_HZ, 1);
          digitalWrite(IN3_HZ, 0);
          digitalWrite(IN4_HZ, 1);
          stepperState[0] = 0;
        break;
      case 1:
          digitalWrite(IN1_HZ, 1);
          digitalWrite(IN2_HZ, 0);
          digitalWrite(IN3_HZ, 0);
          digitalWrite(IN4_HZ, 1);
          stepperState[0] = 1;
        break;
      case 2:
          digitalWrite(IN1_HZ, 1);
          digitalWrite(IN2_HZ, 0);
          digitalWrite(IN3_HZ, 1);
          digitalWrite(IN4_HZ, 0);
          stepperState[0] = 2;
        break;
      case 3:
          digitalWrite(IN1_HZ, 0);
          digitalWrite(IN2_HZ, 1);
          digitalWrite(IN3_HZ, 1);
          digitalWrite(IN4_HZ, 0);
          stepperState[0] = 3;
        break;
    }

  }
  else if(motor == 1) {

    switch(state) {
      case 0:
          digitalWrite(IN1_VT, 0);
          digitalWrite(IN2_VT, 1);
          digitalWrite(IN3_VT, 0);
          digitalWrite(IN4_VT, 1);
          stepperState[1] = 0;
        break;
      case 1:
          digitalWrite(IN1_VT, 1);
          digitalWrite(IN2_VT, 0);
          digitalWrite(IN3_VT, 0);
          digitalWrite(IN4_VT, 1);
          stepperState[1] = 1;
        break;
      case 2:
          digitalWrite(IN1_VT, 1);
          digitalWrite(IN2_VT, 0);
          digitalWrite(IN3_VT, 1);
          digitalWrite(IN4_VT, 0);
          stepperState[1] = 2;
        break;
      case 3:
          digitalWrite(IN1_VT, 0);
          digitalWrite(IN2_VT, 1);
          digitalWrite(IN3_VT, 1);
          digitalWrite(IN4_VT, 0);
          stepperState[1] = 3;
        break;
    }
  }
}

void reverse(int i, int j, int motor) {

  while (1)   {
    switch(stepperState[motor]) {
      case 0:
        setState(3,motor);
        break;
      case 1:
        setState(0,motor);
        break;
      case 2:
        setState(1,motor); 
        break;
      case 3: 
        setState(2,motor);
        break;
      delay(j);  
    }
    i--;
    if (i < 1) break;
  }
}  

void forward(int i, int j, int motor) {

  while (1)   {
    switch(stepperState[motor]) {
      case 0:
        setState(1,motor);
        break;
      case 1:
        setState(2,motor);
        break;
      case 2:
        setState(3,motor); 
        break;
      case 3: 
        setState(0,motor);
        break;
    }
    delay(j);  
    i--;
    if (i < 1) break;
  }
}  

