# Day 28: BME280 Weather Station with I2C LCD

## Overview
Today's topic was a weather station that uses a BME280 sensor and an I2C LCD. I worked on it in Wokwi with an Arduino and an I2C scanner. The scanner detected the LCD on the I2C bus, and I learned that the BME280 in Wokwi is a custom chip, not one of its built-in parts. This report explains what I2C is, what the BME280 measures, and what I found.

## What Is I2C?
I2C is a way for several devices to talk to the Arduino over just two signal lines: **SDA** carries the data and **SCL** carries the clock. Every device on the bus has its own address, so a sensor and an LCD can share the same two wires and the Arduino can still talk to each one separately. On the Arduino Uno, SDA is pin A4 and SCL is pin A5.

## What Each Reading Means
The BME280 measures three things:
- **Temperature (°C):** how hot or cold the air is.
- **Relative humidity (%):** how much water vapour the air holds compared with the most it could hold at that temperature.
- **Atmospheric pressure (hPa):** the weight of the air above the sensor. Normal sea-level pressure is about 1013 hPa, and falling pressure often means the weather is changing.

On a 16x2 LCD these three readings can be shown across two pages so all of them are easy to read.

## I2C Addresses
| Device | I2C address | Where it came from |
|---|---|---|
| 16x2 I2C LCD | 0x27 | Found by my I2C scanner in Wokwi |
| BME280 sensor | 0x76 | The address used in the class sketch (`#define Addr 0x76`) |

An I2C scanner tries every address from 1 to 126 and prints the ones that answer in the Serial Monitor. My scan found one device at `0x27`, which is the LCD. The BME280 did not appear in my scan.

## What Went Wrong and How I Handled It
**Problem:** the BME280 was missing from my scan. I searched Wokwi's parts list for it and found nothing.

**What I found:** the BME280 in Wokwi's examples is a **custom chip**. It is added with two extra files, `bme280.chip.json` and `bme280.chip.c`, and is not a built-in part. The chip code I opened was still the empty starter template, so it could not answer on the I2C bus. Wokwi's built-in list does include the BMP180, a similar I2C pressure and temperature sensor.

**What I would do next:** open the original working project that includes the finished chip code, or use the built-in BMP180 and note that it has no humidity.

## Sketches
I prepared these sketches for the project:
- [Day28_I2C_Scanner.ino](../Projects/Day-28/Day28_I2C_Scanner.ino) – the scanner I ran in Wokwi
- [Day28_BME280_Weather_Station.ino](../Projects/Day-28/Day28_BME280_Weather_Station.ino) – a two-page BME280 weather station (temperature and humidity on page 1, pressure on page 2). I did not run it, because the BME280 chip did not work in my simulation.
- [Day28_BMP180_Weather_Station.ino](../Projects/Day-28/Day28_BMP180_Weather_Station.ino) – the same idea for the built-in BMP180, which measures temperature and pressure. I did not run this either.

## What I Learned
- I2C lets many devices share two wires, SDA for data and SCL for the clock, as long as each has its own address.
- An I2C scanner confirms that the Arduino can detect each device and shows its address. It is the first check when a sensor does not respond.
- The BME280 measures temperature, relative humidity and pressure.
- A part shown in an example may be a custom chip. Without working chip code, the simulation cannot answer on the bus, so the scanner will not find it.
- A small LCD can show more information by splitting it across pages.

## Conclusion
Day 28 introduced I2C and the BME280. The scanner showed how to confirm which devices the Arduino can see, and the missing BME280 showed why checking for the address comes before debugging the rest of the code.
