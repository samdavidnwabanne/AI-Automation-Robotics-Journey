// Day 16 - Blink (SLOW: 2000 ms) with Serial Monitor output
// Circuit: pin 13 -> resistor -> LED anode (long leg), LED cathode (short leg) -> GND

int redLed = 13;

void setup() {
  pinMode(redLed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(redLed, HIGH);
  Serial.println("LED ON");
  delay(2000);

  digitalWrite(redLed, LOW);
  Serial.println("LED OFF");
  delay(2000);
}
