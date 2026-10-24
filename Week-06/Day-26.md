# Day 26: DHT11 & Ultrasonic Sensor Integration

## Overview
Today's class covered two sensors: the DHT11 for temperature and humidity, and the HC-SR04 for distance. In class I built an HC-SR04 ultrasonic distance sensor circuit with an I2C LCD display in Tinkercad Circuits to measure distances and show live centimetre readings. This report explains what each sensor measures and how it works.

## Daily Report
**Day / Week:** Day 26, Week 6

**Topic:** DHT11 and HC-SR04 ultrasonic sensor integration

**Objective:** Understand what the DHT11 and the HC-SR04 measure, how they work, and how both can be used in one Arduino sketch that handles failed readings.

**Activities:** I built an HC-SR04 ultrasonic distance circuit with an I2C LCD in Tinkercad Circuits and checked the live distance readings. I also studied how the DHT11 is read with the DHT sensor library.

## What Each Sensor Measures and How It Works
**DHT11 (temperature and humidity).** The DHT11 measures both temperature and humidity. It sends its readings to the Arduino as a digital signal on one data pin. With the DHT sensor library, `dht.readTemperature()` and `dht.readHumidity()` return the values, which can be shown on the Serial Monitor. It is accurate to about ±2 °C and ±5 % humidity, and it should only be read about once every 2 seconds.

**HC-SR04 (distance).** The HC-SR04 measures distance with sound that humans cannot hear. The Arduino sends a short pulse to the TRIG pin, and the sensor sends out ultrasonic pulses. The ECHO pin stays HIGH for as long as the sound takes to travel to an object and come back. The distance is calculated as:

`distance (cm) = echo time × 0.0343 ÷ 2`

I divide by 2 because the sound travels to the object and back. The calculated distance can be compared with a ruler to check the reading.

## Using Both Sensors in One Sketch
Both sensors can be combined in one Arduino sketch to display temperature, humidity and distance readings. The code must also account for failed readings so that invalid results are handled properly:
- **DHT11:** check `isnan(temperature) || isnan(humidity)` and skip the reading if it failed.
- **HC-SR04:** a reading of 0 means no echo came back, so it is ignored.

## Visuals
**HC-SR04 and I2C LCD circuit in Tinkercad**

![Ultrasonic sensor and LCD circuit](../Projects/Images/Sensors%20Day%2026%20%28circuit%29.PNG)

**Code and Serial Monitor output**

![Code and Serial Monitor](../Projects/Images/Sensors%20Day%2026%20%28code%20%26%20serial%20monitor%29.PNG)

## Code
```cpp
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define trigPin 9
#define echoPin 10

void setup() {
  Serial.begin(9600);              // start the Serial Monitor

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Distance Sensor");
  delay(2000);
  lcd.clear();
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long echoTime = pulseIn(echoPin, HIGH, 30000);

  lcd.clear();

  if (echoTime == 0) {
    lcd.setCursor(0, 0);
    lcd.print("No Echo Received");
    Serial.println("No echo received");
  }
  else {
    float distanceCM = echoTime * 0.0343 / 2.0;

    lcd.setCursor(0, 0);
    lcd.print("Distance:");

    lcd.setCursor(0, 1);
    lcd.print(distanceCM, 1);
    lcd.print(" cm");

    Serial.print("Distance: ");
    Serial.print(distanceCM, 1);
    Serial.println(" cm");
  }

  delay(500);
}
```

The sketch handles a failed reading: if `pulseIn()` returns 0, no echo came back, so the LCD and the Serial Monitor show "No Echo Received" instead of a distance.

## Question I Still Have
Why does the distance reading change slightly even when the object has not moved, and how can I smooth it out so the LCD display stays steady?

## What I Learned
- The DHT11 measures temperature and humidity, and reads must be at least 2 seconds apart.
- The HC-SR04 measures distance from the echo time of ultrasonic pulses, so the distance is the echo time × 0.0343 ÷ 2.
- A distance reading can be checked against a ruler.
- Code should always check for failed readings, using `isnan()` for the DHT11 and treating 0 as no echo for the ultrasonic sensor.

## Conclusion
Day 26 showed how two different sensors measure the world: one through a digital data signal and one through timing an echo. Building the ultrasonic distance circuit with an I2C LCD in Tinkercad connected the theory to a live reading, and handling failed readings is what keeps the results trustworthy.
