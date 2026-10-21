// Day 24 - Exercise 4a: test the servo alone (0, 90, 180 degrees)
#include <Servo.h>

Servo door;

void setup() {
  door.attach(6);
}

void loop() {
  door.write(0);
  delay(1500);
  door.write(90);
  delay(1500);
  door.write(180);
  delay(1500);
}
