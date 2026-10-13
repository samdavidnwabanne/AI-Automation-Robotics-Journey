// Day 19 - Smart Systems: Automatic Night Light
// Sense -> Think -> Act
//   SENSE: LDR voltage divider on A0 (higher reading = brighter)
//   THINK: hysteresis with two thresholds (prevents flickering)
//   ACT:   LED on pin 13 (through a 220 ohm resistor)
//
// Calibration (from my Day 17 readings): Dark = 54, Bright = 974
//   LED turns ON  when the reading falls below 400
//   LED turns OFF when the reading rises above 600
//   Between 400 and 600 the LED keeps its last state.

int ldrPin = A0;
int ledPin = 13;

int onBelow = 400;    // dark enough -> LED ON
int offAbove = 600;   // bright enough -> LED OFF

bool ledOn = false;   // remembers the current LED state

unsigned long lastPrint = 0;   // time of the last Serial print

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // SENSE
  int lightValue = analogRead(ldrPin);

  // THINK
  if (lightValue < onBelow) {
    ledOn = true;
  } else if (lightValue > offAbove) {
    ledOn = false;
  }

  // ACT
  digitalWrite(ledPin, ledOn ? HIGH : LOW);

  // Print the reading and LED state once every second
  if (millis() - lastPrint >= 1000) {
    lastPrint = millis();
    Serial.print("LDR: ");
    Serial.print(lightValue);
    Serial.print(" | LED: ");
    Serial.println(ledOn ? "ON" : "OFF");
  }

  delay(20);   // short pause so the system reacts quickly but stays stable
}
