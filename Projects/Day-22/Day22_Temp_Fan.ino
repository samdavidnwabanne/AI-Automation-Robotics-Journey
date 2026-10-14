// Day 22 - Exercise 5 (Level Up): Temperature-controlled fan
// TMP36 on A1 (5V, signal, GND). Same motor driver as Exercise 1 (pin 5).
// Below 25 C the motor is off. At 35 C it runs at full speed.
// In between, the speed rises smoothly with the temperature.

const int motorPin = 5;      // PWM pin (~)
const int tempPin = A1;

const float minTemp = 25.0;  // motor off below this
const float maxTemp = 35.0;  // full speed at this temperature

unsigned long lastPrint = 0;

void setup() {
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Read the TMP36 and convert to degrees Celsius
  float voltage = analogRead(tempPin) * 5.0 / 1024.0;
  float tempC = (voltage - 0.5) * 100.0;

  // Map 25-35 C to a speed of 0-255 (map works with whole numbers, so use tenths of a degree)
  long tenths = constrain((long)(tempC * 10), (long)(minTemp * 10), (long)(maxTemp * 10));
  int speed = map(tenths, (long)(minTemp * 10), (long)(maxTemp * 10), 0, 255);
  speed = constrain(speed, 0, 255);

  analogWrite(motorPin, speed);

  if (millis() - lastPrint >= 500) {
    lastPrint = millis();
    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print(" C | Fan speed: ");
    Serial.print(map(speed, 0, 255, 0, 100));
    Serial.println(" %");
  }
}
