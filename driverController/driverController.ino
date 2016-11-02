#include <Wire.h>

char junk;
String inputString="";

char curData = 0;

void setup() {

  Wire.begin();
  Serial.begin(9600);
  pinMode(13, INPUT);
  delay(2000);
}

void loop() {
  if(Serial.available()){
    while(Serial.available()) {
      char inChar = (char)Serial.read(); //read the input
      inputString += inChar;        //make a string of the characters coming on serial
    }

    readAndTransmit(inputString);
    while (Serial.available() > 0) { 
      junk = Serial.read(); // clear the serial buffer
    }      

    inputString = "";
  }

  delay(500);
  if(digitalRead(13) == HIGH) {
    delay(500);
    Serial.println("1");
  }
  delay(500);
}

void readAndTransmit(String inputString) {

  int str_len = inputString.length(); 
  //Serial.println("Length of String:");
  //Serial.println(str_len);
  int comma_position1 = inputString.indexOf(',');
  int comma_position2 = inputString.lastIndexOf(',');
  //Serial.println("Comma position");
  //Serial.println(comma_position1);

  String x_str, y_str, laser_str;
  y_str = inputString.substring(comma_position1+1, comma_position2);
  x_str = inputString.substring(0, comma_position1);
  laser_str= inputString.substring(comma_position2+1);

  //Serial.println("xstr:");
  //Serial.println(x_str);
  //Serial.println("ystr:");
  //Serial.println(y_str);
  //Serial.println("laser_str:");
  //Serial.println(laser_str);

  int x,y,l;
  x = x_str.toInt();
  y = y_str.toInt();
  l = laser_str.toInt();
  
  byte data[5];
  unsigned long n = 175;
  
  data[0] = (x >> 8) & 0xFF;
  data[1] = x & 0xFF;
  data[2] = (y >> 8) & 0xFF;
  data[3] = y & 0xFF;
  data[4] = l & 0xFF;
  //Serial.println("Binary:");
  //Serial.print(data[0],BIN);
  //Serial.println("");
  //Serial.print(data[1],BIN);
  //Serial.println("");
  //Serial.print(data[2],BIN);
  //Serial.println("");
  //Serial.print(data[3],BIN);
  //Serial.println("");
  //Serial.print(data[4],BIN);
  //Serial.println("");
  
  Wire.beginTransmission(1);
  Wire.write(data[0]);
  Wire.write(data[1]);
  Wire.write(data[2]);
  Wire.write(data[3]);
  Wire.write(data[4]);
  Wire.endTransmission();
}
