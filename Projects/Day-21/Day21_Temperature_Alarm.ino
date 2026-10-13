// Day 21 - Temperature Sensing & Alert Systems: Temperature Alarm
//
// Parts: TMP36 (A1), push button (pin 2, INPUT_PULLUP), green LED (pin 8),
//        red LED (pin 9), buzzer (pin 7). Each LED uses a 220 ohm resistor.
//
// States:
//   DISARMED : everything off
//   ARMED    : green LED on. Slow beeps above 28 C (warning)
//   ALARM!   : above 30 C while armed. Red LED on + siren.
//              The alarm stays on until the button is pressed, even if
//              the temperature drops.
//
// Button: first press arms the system, the next press disarms everything.
//
// Level reached: Level 1 (state messages in the Serial Monitor)
//                + Level 3 (slow beeps above 28 C, full siren above 30 C)

// ---------- 1. PIN SETUP ----------
const int tempPin = A1;
const int buttonPin = 2;
const int buzzerPin = 7;
const int greenLed = 8;
const int redLed = 9;

// ---------- Settings ----------
const float warnTemp = 28.0;      // slow beeps above this
const float alarmTemp = 30.0;     // alarm starts above this

// ---------- State variables ----------
bool armed = false;
bool alarmOn = false;
bool lastButton = HIGH;
unsigned long lastPress = 0;
unsigned long lastPrint = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);   // pressed = LOW
  pinMode(buzzerPin, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  Serial.begin(9600);
  Serial.println("DISARMED");
}

// ---------- 2. SENSOR READING ----------
float readTemperature() {
  float voltage = analogRead(tempPin) * 5.0 / 1024.0;
  return (voltage - 0.5) * 100.0;
}

void loop() {
  float tempC = readTemperature();

  // ---------- 3. BUTTON: arm / disarm ----------
  bool button = digitalRead(buttonPin);
  if (button == LOW && lastButton == HIGH && millis() - lastPress > 200) {
    lastPress = millis();                 // simple debounce
    if (armed || alarmOn) {
      armed = false;                      // disarm everything
      alarmOn = false;
      Serial.println("DISARMED");
    } else {
      armed = true;
      Serial.println("ARMED");
    }
  }
  lastButton = button;

  // ---------- 4. CONDITIONAL LOGIC ----------
  if (armed && !alarmOn && tempC > alarmTemp) {
    alarmOn = true;                       // latched until the button is pressed
    Serial.println("ALARM!");
  }

  // ---------- 5. OUTPUT CONTROL ----------
  digitalWrite(greenLed, (armed && !alarmOn) ? HIGH : LOW);
  digitalWrite(redLed, alarmOn ? HIGH : LOW);

  if (alarmOn) {
    // siren: flip between two pitches every 150 ms, without delay()
    if ((millis() / 150) % 2 == 0) {
      tone(buzzerPin, 1200);
    } else {
      tone(buzzerPin, 800);
    }
  } else if (armed && tempC > warnTemp) {
    // warning: slow beeps (500 ms on, 500 ms off)
    if ((millis() / 500) % 2 == 0) {
      tone(buzzerPin, 1000);
    } else {
      noTone(buzzerPin);
    }
  } else {
    noTone(buzzerPin);
  }

  // Print the temperature every half second for testing
  if (millis() - lastPrint >= 500) {
    lastPrint = millis();
    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.println(" C");
  }
}
