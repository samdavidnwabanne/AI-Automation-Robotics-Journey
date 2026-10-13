// Day 18 - Outputs & Actuators: Step 2 - servo sweeps 0 to 180 degrees and back
//
// Wiring:
//   Servo signal -> pin 9, servo power -> 5V, servo ground -> GND

#include <Servo.h>      // library that controls servo motors

Servo myServo;          // servo object

void setup() {
  myServo.attach(9);    // connect the servo signal wire to pin 9
}

void loop() {
  // sweep from 0 to 180 degrees
  for (int angle = 0; angle <= 180; angle++) {
    myServo.write(angle);
    delay(15);          // short pause so the servo can reach each angle
  }

  // sweep back from 180 to 0 degrees
  for (int angle = 180; angle >= 0; angle--) {
    myServo.write(angle);
    delay(15);
  }
}
