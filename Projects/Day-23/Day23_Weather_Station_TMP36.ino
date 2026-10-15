// Day 23 - Mini Weather Station (Tinkercad version)
// TMP36 on A1 = temperature, potentiometer on A0 = humidity (0-100 %)
// LCD 16x2 in 4-bit mode. Red LED on pin 6, button on pin 8.
// Level up: "Too hot!" / "Nice" + red LED above 30 C, button toggles C / F.
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int tempPin = A1;
const int humPin  = A0;
const int ledPin  = 6;
const int btnPin  = 8;
const float hotLimit = 30.0;

bool useF = false;
bool lastBtn = HIGH;
unsigned long lastUpdate = 0;

void showReadings() {
  float v = analogRead(tempPin) * 5.0 / 1024.0;
  float tempC = (v - 0.5) * 100.0;
  int hum = map(analogRead(humPin), 0, 1023, 0, 100);

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  if (useF) { lcd.print(tempC * 9.0 / 5.0 + 32.0, 1); lcd.print(" F"); }
  else      { lcd.print(tempC, 1);                    lcd.print(" C"); }
  lcd.print(tempC > hotLimit ? " HOT" : " OK ");   // fixed width, no clear()

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(hum);
  lcd.print(" %  ");

  digitalWrite(ledPin, tempC > hotLimit ? HIGH : LOW);
}

void setup() {
  lcd.begin(16, 2);
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
  showReadings();
}

void loop() {
  bool btn = digitalRead(btnPin);
  if (lastBtn == HIGH && btn == LOW) {      // button pressed
    useF = !useF;
    lcd.clear();                            // unit text changes length
    showReadings();
    delay(50);                              // debounce
  }
  lastBtn = btn;

  if (millis() - lastUpdate >= 2000) {      // update every 2 s
    lastUpdate = millis();
    showReadings();
  }
}
