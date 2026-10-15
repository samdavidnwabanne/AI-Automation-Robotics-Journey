// Day 23 - Mini Weather Station (DHT11 version for real hardware)
// DHT11 data -> pin 7, LCD 4-bit (12,11,5,4,3,2), red LED pin 6, button pin 8.
#include <LiquidCrystal.h>
#include <DHT.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DHT dht(7, DHT11);

const int ledPin = 6;
const int btnPin = 8;
const float hotLimit = 30.0;

bool useF = false;
bool lastBtn = HIGH;
unsigned long lastUpdate = 0;

void showReadings() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(t) || isnan(h)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor error    ");
    return;
  }
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  if (useF) { lcd.print(t * 9.0 / 5.0 + 32.0, 1); lcd.print(" F"); }
  else      { lcd.print(t, 1);                    lcd.print(" C"); }
  lcd.print(t > hotLimit ? " HOT" : " OK ");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(h, 0);
  lcd.print(" %  ");

  digitalWrite(ledPin, t > hotLimit ? HIGH : LOW);
}

void setup() {
  lcd.begin(16, 2);
  dht.begin();
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
  delay(2000);
  showReadings();
}

void loop() {
  bool btn = digitalRead(btnPin);
  if (lastBtn == HIGH && btn == LOW) {
    useF = !useF;
    lcd.clear();
    showReadings();
    delay(50);
  }
  lastBtn = btn;

  if (millis() - lastUpdate >= 2000) {
    lastUpdate = millis();
    showReadings();
  }
}
