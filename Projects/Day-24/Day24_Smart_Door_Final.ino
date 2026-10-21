// Day 24 - Exercise 6: Smart Door, level up (all three options)
//  1. Door stays open while someone is there and closes 2 s after they leave (millis, no delay)
//  2. Short buzzer beep at the moment the door opens (buzzer on pin 4)
//  3. Lock button on pin 2: press to lock/unlock; while locked the sensor is ignored
// Ultrasonic SIG -> 7, servo -> 6, red LED -> 8, green LED -> 12, pot A0 (from Exercise 4, unused here)
#include <Servo.h>

const int sigPin    = 7;
const int servoPin  = 6;
const int redLed    = 8;
const int greenLed  = 12;
const int buzzerPin = 4;
const int lockBtn   = 2;

const int openDistance = 20;             // cm
const unsigned long holdTime = 2000;     // ms the door stays open after the person leaves

Servo door;
bool isOpen = false;
bool locked = false;
bool lastBtn = HIGH;
unsigned long lastSeen = 0;

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

void setDoor(bool open) {
  isOpen = open;
  door.write(open ? 90 : 0);
  digitalWrite(greenLed, open ? HIGH : LOW);
  digitalWrite(redLed, open ? LOW : HIGH);
  if (open) tone(buzzerPin, 1000, 150);  // short beep as the door opens
}

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(lockBtn, INPUT_PULLUP);
  door.attach(servoPin);
  Serial.begin(9600);
  setDoor(false);
}

void loop() {
  // lock button: act once per press
  bool btn = digitalRead(lockBtn);
  if (lastBtn == HIGH && btn == LOW) {
    locked = !locked;
    if (locked && isOpen) setDoor(false);   // locking closes the door
    delay(50);                              // debounce
  }
  lastBtn = btn;

  long distance = readDistanceCm(sigPin);
  bool someoneNear = (distance > 0 && distance < openDistance);

  if (!locked) {
    if (someoneNear) {
      lastSeen = millis();
      if (!isOpen) setDoor(true);
    } else if (isOpen && millis() - lastSeen >= holdTime) {
      setDoor(false);
    }
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Door: ");
  Serial.print(isOpen ? "OPEN" : "CLOSED");
  Serial.println(locked ? " | LOCKED" : "");
  delay(50);
}
