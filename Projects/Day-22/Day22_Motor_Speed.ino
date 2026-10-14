// Day 22 - Exercise 3: Motor speed control with a potentiometer
// Potentiometer: outer legs to 5V and GND, middle leg to A0
// The button (pin 2) still turns the motor on and off.
// The Serial Monitor prints the speed as a percentage from 0 to 100.

const int motorPin = 5;      // PWM pin (~)
const int buttonPin = 2;
const int ledPin = 8;
const int potPin = A0;

bool motorOn = false;
bool lastButton = HIGH;
unsigned long lastPrint = 0;

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // --- Button: toggle the motor on and off ---
  bool button = digitalRead(buttonPin);
  if (lastButton == HIGH && button == LOW) {
    motorOn = !motorOn;
    delay(50);                                     // debounce
  }
  lastButton = button;

  // --- Potentiometer: read and convert to a speed ---
  int potValue = analogRead(potPin);               // 0 - 1023
  int speed = map(potValue, 0, 1023, 0, 255);      // 0 - 255 for analogWrite
  int percent = map(potValue, 0, 1023, 0, 100);    // 0 - 100 for display

  // --- Output ---
  if (motorOn) {
    analogWrite(motorPin, speed);
    digitalWrite(ledPin, HIGH);
  } else {
    analogWrite(motorPin, 0);
    digitalWrite(ledPin, LOW);
  }

  // Print the speed twice a second
  if (millis() - lastPrint >= 500) {
    lastPrint = millis();
    Serial.print("Motor: ");
    Serial.print(motorOn ? "ON" : "OFF");
    Serial.print(" | Speed: ");
    Serial.print(motorOn ? percent : 0);
    Serial.println(" %");
  }
}
