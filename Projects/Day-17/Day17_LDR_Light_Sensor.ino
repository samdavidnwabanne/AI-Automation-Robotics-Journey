// Day 17 - Inputs & Sensors: LDR light sensor
// LED turns ON automatically when the light level drops below the threshold.
//
// Wiring (voltage divider):
//   5V -> LDR -> A0 -> 10k resistor -> GND
//   Pin 7 -> 220 ohm resistor -> LED anode (long leg), LED cathode (short leg) -> GND
//
// Measured readings (Serial Monitor):
//   Dark (sensor covered) = 54
//   Bright                = 974
//   Threshold = (54 + 974) / 2 = 514

int ldrPin = A0;
int ledPin = 7;

int threshold = 514;

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