// Day 17 - Inputs & Sensors: LDR light sensor
// LED turns ON automatically when the light level drops below the threshold.
//
// Wiring (voltage divider):
//   5V -> LDR -> A0 -> 10k resistor -> GND
//   Pin 7 -> 220 ohm resistor -> LED anode (long leg), LED cathode (short leg) -> GND

int ldrPin = A0;
int ledPin = 7;

// Set this midway between YOUR two readings from the Serial Monitor:
//   bright reading and covered (dark) reading.
// Example: bright = 700, dark = 150  ->  threshold = 400
int threshold = 400;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int lightValue = analogRead(ldrPin);
  Serial.println(lightValue);

  if (lightValue < threshold) {
    digitalWrite(ledPin, HIGH);   // dark: LED ON
  } else {
    digitalWrite(ledPin, LOW);    // bright: LED OFF
  }

  delay(500);
}
