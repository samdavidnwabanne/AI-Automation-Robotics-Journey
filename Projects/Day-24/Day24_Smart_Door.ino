// Day 24 - Exercise 5: Smart Door
// Ultrasonic SIG -> pin 7, servo signal -> pin 6,
// red LED -> pin 8, green LED -> pin 12 (each through 220 ohm to GND).
// Closer than 20 cm (and above 0): servo 90 degrees (open) + green LED.
// Otherwise: servo 0 degrees (closed) + red LED.
#include <Servo.h>

const int sigPin   = 7;
const int servoPin = 6;
const int redLed   = 8;
const int greenLed = 12;

Servo door;

// Returns the distance in cm, or 0 if there is no echo.
long readDistanceCm(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  digitalWrite(pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pin, LOW);

  pinMode(pin, INPUT);
  long duration = pulseIn(pin, HIGH, 30000);
  return duration / 58;
}

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  door.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  long distance = readDistanceCm(sigPin);

  if (distance > 0 && distance < 20) {   // ignore 0 = no echo
    door.write(90);                      // open
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
  } else {
    door.write(0);                       // closed
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(100);
}
