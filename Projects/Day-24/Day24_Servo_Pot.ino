// Day 24 - Exercise 4b: control the servo with a potentiometer on A0
#include <Servo.h>

Servo door;

void setup() {
  door.attach(6);
}

void loop() {
  int reading = analogRead(A0);              // 0 - 1023
  int angle = map(reading, 0, 1023, 0, 180); // 0 - 180 degrees
  door.write(angle);
  delay(15);                                 // let the servo move
}
