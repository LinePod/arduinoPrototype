#include <Wire.h>

void setup() {
  Wire.begin();
  pinMode(13, INPUT);
}

boolean flag = true;

void loop() {
  if (flag == true) {
    // 1 //
    transmit_data(97, 157, 0);
    delay(500);
    while (digitalRead(13) == LOW) {};

    // 2 //
    transmit_data(117, 137, 0);
    delay(500);
    while (digitalRead(13) == LOW) {};

    // 3 //
    transmit_data(137, 117, 0);
    delay(500);
    while (digitalRead(13) == LOW) {};

    /*
    // 4 //
    transmit_data(150, 150, 0);
    delay(500);
    while (digitalRead(13) == LOW) {};

    // 5 //
    transmit_data(150, 150, 0);
    delay(500);
    while (digitalRead(13) == LOW) {};

    // 6 //
    transmit_data(150, 150, 0);
    delay(500);
    while (digitalRead(13) == LOW) {};

    // 7 //
    transmit_data(150, 150, 0);
    delay(500);
    while (digitalRead(13) == LOW) {};

    // 8 //
    transmit_data(150, 150, 0);
    delay(500);
    while (digitalRead(13) == LOW) {};
    */
  }
  flag = false;
}

void transmit_data(byte vector_x, byte vector_y, byte laser_state) {
  Wire.beginTransmission(1);
  Wire.write(vector_x);
  Wire.write(vector_y);
  Wire.write(laser_state);
  Wire.endTransmission();
}
