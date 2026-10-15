// Day 23 - Exercise 3: DHT11 on pin 7 -> Serial Monitor every 2 s
// Needs the Adafruit "DHT sensor library" (real hardware / simulators that have a DHT11).
#include <DHT.h>

#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);                           // DHT11 can be read at most every 2 s
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(t) || isnan(h)) {
    Serial.println("Sensor read failed (nan)");
    return;
  }
  Serial.print("Temp: ");
  Serial.print(t, 1);
  Serial.print(" C  Humidity: ");
  Serial.print(h, 0);
  Serial.println(" %");
}
