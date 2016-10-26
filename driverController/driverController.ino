#include <Wire.h>

byte dataToSend[4][3];

char curData = 0;

void setup() {
  dataToSend[0][0] = 157;
  dataToSend[0][1] = 127;
  dataToSend[0][2] = 1;

  dataToSend[1][0] = 127;
  dataToSend[1][1] = 157;
  dataToSend[1][2] = 1;

  dataToSend[2][0] = 97;
  dataToSend[2][1] = 127;
  dataToSend[2][2] = 1;

  dataToSend[3][0] = 127;
  dataToSend[3][1] = 97;
  dataToSend[3][2] = 1;

  Wire.begin();
  Serial.begin(9600);
  pinMode(13, INPUT);
  delay(2000);
}

void loop() {
  if(digitalRead(13) == HIGH) {
    transmit_data(dataToSend[curData]);
    if(curData < sizeof(dataToSend)/sizeof(dataToSend[0])-1) {
      curData++;
    }
    else if (curData >= sizeof(dataToSend)/sizeof(dataToSend[0])-1) {
      for(;;); //exit
    }
    delay(2000);
  }
  delay(500);
}

void transmit_data(byte arr[3]) {
  Serial.println("arr:");
  Serial.println(arr[0]);
  Serial.println(arr[1]);
  Serial.println(arr[2]);
  Serial.println("byte:");
  byte vector_x, vector_y, laser_state;
  vector_x = arr[0];
  vector_y = arr[1];
  laser_state = arr[2];
  Serial.println(vector_x);
  Serial.println(vector_y);
  Serial.println(laser_state);
  Serial.println("");
  
  Wire.beginTransmission(1);
  Wire.write(vector_x);
  Wire.write(vector_y);
  Wire.write(laser_state);
  Wire.endTransmission();
}
