// Day 16 - Blink (FAST: 100 ms) with Serial Monitor output
// Circuit: pin 13 -> resistor -> LED anode (long leg), LED cathode (short leg) -> GND

int redLed = 13;

void setup() {
  pinMode(redLed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(redLed, HIGH);
  Serial.println("LED ON");
  delay(100);

  digitalWrite(redLed, LOW);
  Serial.println("LED OFF");
  delay(100);
}
