// Day 22 - Exercise 2: Motor on/off with a push button
// Motor driver: pin 5 -> 1k resistor -> NPN transistor base
// Button: pin 2 to GND (INPUT_PULLUP, pressed = LOW)
// LED: pin 8 through a 220 ohm resistor shows when the motor is on

const int motorPin = 5;
const int buttonPin = 2;
const int ledPin = 8;

bool motorOn = false;
bool lastButton = HIGH;

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  bool button = digitalRead(buttonPin);

  // State-change method: act only at the moment the button goes from HIGH to LOW
  if (lastButton == HIGH && button == LOW) {
    motorOn = !motorOn;                 // toggle the motor state
    Serial.println(motorOn ? "Motor ON" : "Motor OFF");
    delay(50);                          // simple debounce
  }
  lastButton = button;

  if (motorOn) {
    analogWrite(motorPin, 255);         // full speed
    digitalWrite(ledPin, HIGH);
  } else {
    analogWrite(motorPin, 0);
    digitalWrite(ledPin, LOW);
  }
}
