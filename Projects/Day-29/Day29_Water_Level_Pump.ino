// Day 29 - Water-Level Indicator and Automatic Pump Controller
// The ultrasonic sensor sits ABOVE the water: a bigger distance = a lower water level.
//
// Ultrasonic SIG -> pin 7 (3-pin Tinkercad sensor)
// Relay driver   -> pin 4 (transistor + relay, as in Day 22); the relay switches the pump
// Red LED (LOW)  -> pin 8     Green LED (FULL) -> pin 12   (each through 220 ohm to GND)
//
// Rules:
//  distance >= LOW_CM  -> water is LOW  -> pump ON, red LED
//  distance <= FULL_CM -> water is FULL -> pump OFF, green LED
//  in between          -> keep the pump in its current state (no flickering)
//  distance 0          -> no echo -> ignore the reading

// ---------- Pins ----------
const int SIG_PIN   = 7;
const int RELAY_PIN = 4;
const int RED_LED   = 8;
const int GREEN_LED = 12;

// ---------- Relay level (change here if your relay is active LOW) ----------
const int RELAY_ON  = HIGH;
const int RELAY_OFF = LOW;

// ---------- Thresholds in cm (measured from the sensor down to the water) ----------
const int FULL_CM  = 5;    // water at or closer than this = FULL
const int LOW_CM   = 20;   // water at or farther than this = LOW
const int EMPTY_CM = 30;   // distance to the bottom of the tank = 0 %

bool pumpOn = false;

// Returns the distance in cm, or 0 if there is no echo.
long readDistanceCm(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  digitalWrite(pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin, LOW);

  pinMode(pin, INPUT);
  long duration = pulseIn(pin, HIGH, 30000);
  return duration / 58;
}

void setup() {
  digitalWrite(RELAY_PIN, RELAY_OFF);   // set the level before pinMode so it does not click on
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // ---------- 1. SENSE ----------
  long distance = readDistanceCm(SIG_PIN);

  if (distance == 0) {                  // no echo: do not decide on a bad reading
    Serial.println("No echo - reading ignored");
    delay(500);
    return;
  }

  // Estimated water level: FULL_CM = 100 %, EMPTY_CM = 0 %
  int levelPercent = map(distance, EMPTY_CM, FULL_CM, 0, 100);
  levelPercent = constrain(levelPercent, 0, 100);

  // ---------- 2. DECIDE ----------
  const char* status = "NORMAL";
  if (distance >= LOW_CM) {
    pumpOn = true;                      // water is low: fill it
    status = "LOW";
  } else if (distance <= FULL_CM) {
    pumpOn = false;                     // water is full: stop
    status = "FULL";
  }

  // ---------- 3. ACT ----------
  digitalWrite(RELAY_PIN, pumpOn ? RELAY_ON : RELAY_OFF);
  digitalWrite(RED_LED, strcmp(status, "LOW") == 0 ? HIGH : LOW);
  digitalWrite(GREEN_LED, strcmp(status, "FULL") == 0 ? HIGH : LOW);

  // ---------- 4. SERIAL MONITOR ----------
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Level: ");
  Serial.print(levelPercent);
  Serial.print(" % | Status: ");
  Serial.print(status);
  Serial.print(" | Pump: ");
  Serial.println(pumpOn ? "ON" : "OFF");

  delay(500);
}
