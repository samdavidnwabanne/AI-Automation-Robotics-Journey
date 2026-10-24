// Day 28 - Weather station with I2C LCD (Wokwi version using a BMP180)
// The BMP180 and the 16x2 LCD share SDA (A4) and SCL (A5).
// The LCD shows two pages: page 1 = temperature, page 2 = pressure.
// (The BME280 version, with humidity too, is Day28_BME280_Weather_Station.ino.)
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_BMP085.h>                 // library that also supports the BMP180

const byte LCD_ADDRESS = 0x27;               // from the I2C scanner
const unsigned long PAGE_MS = 3000;          // how long each page shows

LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);
Adafruit_BMP085 bmp;

bool page1 = true;
unsigned long lastSwitch = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  if (!bmp.begin()) {                        // BMP180 answers at address 0x77
    lcd.print("BMP180 not found");
    Serial.println("BMP180 not found - check wiring");
    while (true) {}
  }
  lcd.print("Weather Station");
  delay(2000);
  lcd.clear();
}

void loop() {
  // ---------- 1. READ ----------
  float tempC = bmp.readTemperature();          // degrees Celsius
  float pressure = bmp.readPressure() / 100.0;  // Pa -> hPa

  // ---------- 2. CHECK FOR FAILED READINGS ----------
  if (isnan(tempC) || isnan(pressure)) {
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
    lcd.print("Temperature:    ");
    lcd.setCursor(0, 1);
    lcd.print(tempC, 1);
    lcd.print(" C        ");
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
  Serial.print(" C | Pressure: ");
  Serial.print(pressure, 1);
  Serial.println(" hPa");

  delay(500);
}
