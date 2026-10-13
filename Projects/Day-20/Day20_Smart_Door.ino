// Day 20 - Arduino Practical Challenge: Smart Door (System D)
// An HC-SR04 ultrasonic sensor measures distance.
// When an object is within 30 cm, a servo "opens" the door (90 degrees).
// When the object moves away, the door "closes" (0 degrees).
//
// Wiring:
//   HC-SR04  VCC -> 5V, GND -> GND, Trig -> pin 10, Echo -> pin 11
//   Servo    signal -> pin 9, red -> 5V, brown/black -> GND

#include <Servo.h>

// ---------- 1. PIN SETUP ----------
const int trigPin = 10;
const int echoPin = 11;
const int servoPin = 9;

// ---------- Settings ----------
const int openDistance = 30;      // cm: open the door at or below this distance
const int doorClosed = 0;         // servo angle when closed
const int doorOpen = 90;          // servo angle when open
const unsigned long holdTime = 2000;  // ms the door stays open after the object leaves

Servo doorServo;
bool isOpen = false;
unsigned long lastSeen = 0;       // last time an object was within range

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  doorServo.attach(servoPin);
  doorServo.write(doorClosed);    // start with the door closed
  Serial.begin(9600);
}

// ---------- 2. SENSOR READING ----------
// Returns the distance in cm, or -1 if no echo was received.
float readDistanceCm() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);    // 10 microsecond pulse starts a measurement
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);  // time for the echo to return (30 ms timeout)
  if (duration == 0) {
    return -1;                    // nothing detected
  }
  return (duration * 0.034) / 2;  // speed of sound 0.034 cm/us, divided by 2 (there and back)
}

void loop() {
  float distance = readDistanceCm();

  // ---------- 3. CONDITIONAL LOGIC ----------
  bool objectNear = (distance > 0 && distance <= openDistance);

  if (objectNear) {
    lastSeen = millis();
    if (!isOpen) {
      // ---------- 4. OUTPUT CONTROL ----------
      doorServo.write(doorOpen);
      isOpen = true;
    }
  } else if (isOpen && millis() - lastSeen >= holdTime) {
    doorServo.write(doorClosed);
    isOpen = false;
  }

  // Serial Monitor output for testing
  Serial.print("Distance: ");
  if (distance < 0) {
    Serial.print("no echo");
  } else {
    Serial.print(distance);
    Serial.print(" cm");
  }
  Serial.print(" | Door: ");
  Serial.println(isOpen ? "OPEN" : "CLOSED");

  delay(100);
}
