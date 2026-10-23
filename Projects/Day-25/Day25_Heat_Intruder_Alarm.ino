// Day 25 - Mini Project: Heat & Intruder Alarm
//
// Inputs : TMP36 (A1), LDR + 10k divider (A0), arm/disarm button (pin 2)
// Outputs: buzzer (pin 4), green LED = armed (pin 8), red LED = alarm (pin 12)
//
// Rules:
//  1. HEAT alarm: temperature >= HEAT_ON_C turns it on, and it only clears
//     again below HEAT_OFF_C (hysteresis stops it flickering). Always active.
//  2. INTRUDER alarm: only when ARMED. If the light drops below LIGHT_LIMIT
//     (a shadow or a broken beam) the alarm turns on and stays on.
//  3. Button: toggles armed / disarmed and resets an intruder alarm.

// ---------- Pins ----------
const int LDR_PIN    = A0;
const int TMP_PIN    = A1;
const int BTN_PIN    = 2;
const int BUZZER_PIN = 4;
const int GREEN_LED  = 8;
const int RED_LED    = 12;

// ---------- Limits (chosen by testing) ----------
const float HEAT_ON_C  = 40.0;   // heat alarm on at or above this
const float HEAT_OFF_C = 38.0;   // heat alarm off at or below this
const int LIGHT_LIMIT  = 500;    // light reading below this = intruder
const unsigned long SIREN_MS = 250;   // siren changes tone this often

// ---------- State ----------
bool armed = false;
bool heatAlarm = false;
bool intruderAlarm = false;
bool lastBtn = HIGH;
bool sirenHigh = false;
unsigned long lastSiren = 0;
unsigned long lastPrint = 0;

float readTempC() {
  float voltage = analogRead(TMP_PIN) * 5.0 / 1024.0;
  return (voltage - 0.5) * 100.0;
}

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // ---------- 1. INPUTS ----------
  float tempC = readTempC();
  int light = analogRead(LDR_PIN);
  bool btn = digitalRead(BTN_PIN);

  // ---------- 2. DECISIONS ----------
  if (lastBtn == HIGH && btn == LOW) {     // one press = one toggle
    armed = !armed;
    intruderAlarm = false;                 // any press resets the intruder alarm
    delay(50);                             // debounce
  }
  lastBtn = btn;

  if (tempC >= HEAT_ON_C) heatAlarm = true;
  else if (tempC <= HEAT_OFF_C) heatAlarm = false;

  if (armed && light < LIGHT_LIMIT) intruderAlarm = true;

  // ---------- 3. OUTPUTS ----------
  digitalWrite(GREEN_LED, armed ? HIGH : LOW);
  digitalWrite(RED_LED, (heatAlarm || intruderAlarm) ? HIGH : LOW);

  if (intruderAlarm) {                     // siren: two tones alternating
    if (millis() - lastSiren >= SIREN_MS) {
      lastSiren = millis();
      sirenHigh = !sirenHigh;
      tone(BUZZER_PIN, sirenHigh ? 1200 : 800);
    }
  } else if (heatAlarm) {
    tone(BUZZER_PIN, 1000);                // steady tone for heat
  } else {
    noTone(BUZZER_PIN);
  }

  // ---------- 4. SERIAL MONITOR ----------
  if (millis() - lastPrint >= 500) {
    lastPrint = millis();
    Serial.print("Temp: ");
    Serial.print(tempC, 1);
    Serial.print(" C | Light: ");
    Serial.print(light);
    Serial.print(" | ");
    Serial.print(armed ? "ARMED" : "disarmed");
    if (heatAlarm) Serial.print(" | HEAT ALARM");
    if (intruderAlarm) Serial.print(" | INTRUDER ALARM");
    Serial.println();
  }
  delay(20);
}
