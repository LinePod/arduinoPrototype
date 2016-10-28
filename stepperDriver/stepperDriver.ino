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

const int HZ_FW = 0;
const int HZ_RV = 1;
const int VT_FW = 2;
const int VT_RV = 3;

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
  Serial.begin(9600);
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
  Serial.println("Received bytes:");
  Serial.println(bytes);
  digitalWrite(readyPin, LOW);
  byte c;
  byte x_b[2];
  byte y_b[2];
   
  x_b[0] = Wire.read();
  x_b[1] = Wire.read();
  y_b[0] = Wire.read();
  y_b[1] = Wire.read();
  c = Wire.read();

  int x = *(signed char *)(&x_b[1]);
  x *= 1 << 8;
  x |= x_b[0];
  Serial.println(x);

  int y = *(signed char *)(&y_b[1]);
  y *= 1 << 8;
  y |= y_b[0];
  Serial.println(y);

  go = 1;
  c = Wire.read();
}

void drive(int x, int y) {
  //Serial.println("drive start");
  //Serial.println(stepper_one);
  //Serial.println(stepper_two);
  
  if ((x == 0) && (y == 0)) return;

  int instructions[4] = {HZ_FW, HZ_RV, VT_FW, VT_RV};
  int index_one, index_two;
  int num = abs(x) + abs(y);
  int order[num];

  if (abs(x) < abs(y)) {
    int tmp = x;
    x = y;
    y = tmp;
    index_one = 2;
    index_two = 0;
  }
  else {
    index_one = 0;
    index_two = 2;
  }

  if (x > 0) index_one++;
  if (y > 0) index_two++;

  order[0] = instructions[index_one];
  float y_per_x = (float)abs(y) / (float)abs(x);
  int counter_index = 1;
  int counter_y = 0;
  int i = 0;

  for (i = 1; i <= abs(x); i++) {
    float y_position = (float)i * y_per_x;
    if (y_position - (float)counter_y >= 0.5) {
      order[counter_index] = instructions[index_two];
      counter_y++;
      counter_index++;
      order[counter_index] = instructions[index_one];
    }
    else {
      order[counter_index] = instructions[index_one];
    }
    counter_index++;
  }



  // drive
  for(int i=0; i < num;++i) {
    switch(order[i]) {
      case HZ_FW:
        forward(1,120,0);
        break;
      case HZ_RV:
        reverse(1,120,0);
        break;
      case VT_FW:
        forward(1,120,1);
        break;
      case VT_RV:
        reverse(1,120,1);
        break;
    }
  }
  free(order);
  //Serial.println("drive end");
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
  //Serial.println("reverse, steps: ");
  //Serial.println(i);

  while (1)   {
    switch(stepperState[motor]) {
      case 0:
        setState(3,motor);
        break;
      case 3: 
        setState(2,motor);
        break;
      case 2:
        setState(1,motor); 
        break;
      case 1:
        setState(0,motor);
        break;
    }
    delay(j);  
    i--;
    if (i < 1) break;
  }
}  

void forward(int i, int j, int motor) {

  //Serial.println("forward, steps: ");
  //Serial.println(i);

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

