// Day 25 - Stage 1a: test the temperature sensor alone
// TMP36: left leg 5V, middle leg A1, right leg GND.
const int TMP_PIN = A1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  float voltage = analogRead(TMP_PIN) * 5.0 / 1024.0;
  float tempC = (voltage - 0.5) * 100.0;   // TMP36: 0.5 V = 0 C, 10 mV per degree
  Serial.print("Temp: ");
  Serial.print(tempC, 1);
  Serial.println(" C");
  delay(500);
}
