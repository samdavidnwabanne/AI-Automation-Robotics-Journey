// Day 25 - Stage 1b: test the light sensor alone
// LDR from 5V to A0, with a 10k resistor from A0 to GND.
// Brighter light = bigger number.
const int LDR_PIN = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Light: ");
  Serial.println(analogRead(LDR_PIN));
  delay(500);
}
