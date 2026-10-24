// Day 28 - BME280 weather station with I2C LCD
// BME280 and the 16x2 LCD share SDA (A4) and SCL (A5).
// The LCD shows two pages: page 1 = temperature and humidity, page 2 = pressure.
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

const byte LCD_ADDRESS = 0x27;               // from the I2C scanner
const byte BME_ADDRESS = 0x76;               // from the I2C scanner
const unsigned long PAGE_MS = 3000;          // how long each page shows

LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);
Adafruit_BME280 bme;

bool page1 = true;
unsigned long lastSwitch = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  if (!bme.begin(BME_ADDRESS)) {
    lcd.print("BME280 not found");
    Serial.println("BME280 not found - check wiring and address");
    while (true) {}
  }
  lcd.print("Weather Station");
  delay(2000);
  lcd.clear();
}

void loop() {
  // ---------- 1. READ ----------
  float tempC = bme.readTemperature();         // degrees Celsius
  float humidity = bme.readHumidity();         // percent
  float pressure = bme.readPressure() / 100.0; // Pa -> hPa

  // ---------- 2. CHECK FOR FAILED READINGS ----------
  if (isnan(tempC) || isnan(humidity) || isnan(pressure)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor error    ");
    Serial.println("Sensor read failed");
    delay(1000);
    return;
  }

  // ---------- 3. SWITCH PAGE EVERY 3 SECONDS ----------
  if (millis() - lastSwitch >= PAGE_MS) {
    lastSwitch = millis();
    page1 = !page1;
    lcd.clear();
  }

  // ---------- 4. SHOW THE CURRENT PAGE ----------
  if (page1) {
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(tempC, 1);
    lcd.print(" C   ");
    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(humidity, 0);
    lcd.print(" %  ");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Pressure:       ");
    lcd.setCursor(0, 1);
    lcd.print(pressure, 1);
    lcd.print(" hPa    ");
  }

  // ---------- 5. SERIAL MONITOR ----------
  Serial.print("Temp: ");
  Serial.print(tempC, 1);
  Serial.print(" C | Humidity: ");
  Serial.print(humidity, 0);
  Serial.print(" % | Pressure: ");
  Serial.print(pressure, 1);
  Serial.println(" hPa");

  delay(500);
}
