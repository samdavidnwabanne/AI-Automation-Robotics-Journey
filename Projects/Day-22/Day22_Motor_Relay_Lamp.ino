// Day 22 - DC Motor Control & Relay Switching (final sketch)
//
// Motor driver : pin 5 -> 1k -> NPN transistor base, diode across the motor
// Motor button : pin 2 to GND (INPUT_PULLUP)  -> toggles the motor
// Motor LED    : pin 8 through 220 ohm        -> on while the motor is on
// Speed pot    : middle leg to A0             -> sets the motor speed
// Relay coil   : pin 4 -> 1k -> NPN transistor base, diode across the coil
// Lamp button  : pin 3 to GND (INPUT_PULLUP)  -> toggles the relay lamp
// Lamp         : 5V -> relay COM, relay NO -> 220 ohm -> LED -> GND

// ---------- 1. PIN SETUP ----------
const int motorPin = 5;      // PWM pin (~)
const int motorButton = 2;
const int lampButton = 3;
const int relayPin = 4;
const int ledPin = 8;
const int potPin = A0;

// Change these two lines if the relay is active LOW
const int RELAY_ON = HIGH;
const int RELAY_OFF = LOW;

bool motorOn = false;
bool lampOn = false;
bool lastMotorButton = HIGH;
bool lastLampButton = HIGH;
unsigned long lastPrint = 0;

void setup() {
  digitalWrite(relayPin, RELAY_OFF);   // set the OFF level first so the relay does not click on at start-up
  pinMode(relayPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(motorButton, INPUT_PULLUP);
  pinMode(lampButton, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // ---------- 2. BUTTONS (state-change method) ----------
  bool mButton = digitalRead(motorButton);
  if (lastMotorButton == HIGH && mButton == LOW) {
    motorOn = !motorOn;
    delay(50);                                     // debounce
  }
  lastMotorButton = mButton;

  bool lButton = digitalRead(lampButton);
  if (lastLampButton == HIGH && lButton == LOW) {
    lampOn = !lampOn;
    delay(50);                                     // debounce
  }
  lastLampButton = lButton;

  // ---------- 3. SPEED CONTROL ----------
  int potValue = analogRead(potPin);               // 0 - 1023
  int speed = map(potValue, 0, 1023, 0, 255);      // PWM value
  int percent = map(potValue, 0, 1023, 0, 100);    // speed in %

  // ---------- 4. OUTPUT CONTROL ----------
  if (motorOn) {
    analogWrite(motorPin, speed);
    digitalWrite(ledPin, HIGH);
  } else {
    analogWrite(motorPin, 0);
    digitalWrite(ledPin, LOW);
  }
  digitalWrite(relayPin, lampOn ? RELAY_ON : RELAY_OFF);   // digitalWrite only, never analogWrite, for a relay

  // ---------- Serial Monitor ----------
  if (millis() - lastPrint >= 500) {
    lastPrint = millis();
    Serial.print("Motor: ");
    Serial.print(motorOn ? "ON" : "OFF");
    Serial.print(" | Speed: ");
    Serial.print(motorOn ? percent : 0);
    Serial.print(" % | Lamp: ");
    Serial.println(lampOn ? "ON" : "OFF");
  }
}
