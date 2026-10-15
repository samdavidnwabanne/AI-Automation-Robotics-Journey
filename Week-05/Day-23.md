# Day 23: Temperature Monitoring & LCD Display

## Overview
I built a mini weather station in Tinkercad Circuits. An Arduino Uno reads temperature and humidity and shows both on a 16x2 LCD, refreshing every 2 seconds. I also added a comfort alert with a red LED and a button that switches the display between Celsius and Fahrenheit.

## Concepts Explored
- Wiring a 16x2 LCD in 4-bit mode with the `LiquidCrystal` library
- Positioning text with `lcd.setCursor(col, row)` and printing with `lcd.print()`
- Printing one decimal place with `lcd.print(value, 1)`
- Avoiding `lcd.clear()` flicker by overwriting old text with trailing spaces
- Reading temperature with a TMP36 and converting the voltage to °C
- Mapping a potentiometer to a 0–100 humidity value with `map()`
- Updating every 2 seconds without blocking, using `millis()`
- Reading a push button with `INPUT_PULLUP` and a simple debounce
- Converting Celsius to Fahrenheit: F = C × 9/5 + 32
- Checking sensor readings with `isnan()` (DHT11 sketches)

## What I Built
**LCD test.** I wired the LCD in 4-bit mode (RS to pin 12, E to pin 11, D4–D7 to pins 5, 4, 3, 2) and printed "Hello, Robotics!" on line 1 with a running seconds counter on line 2.

**Weather station.** Tinkercad does not have a DHT11, so I used a TMP36 on A1 for temperature and a potentiometer on A0 as a stand-in for humidity, mapped to 0–100 %. Line 1 shows the temperature and line 2 shows the humidity, updated every 2 seconds.

**Level up.** If the temperature goes above 30 °C, the LCD shows "HOT" and a red LED on pin 6 turns on. A push button on pin 8 switches the temperature between °C and °F.

I also wrote two DHT11 sketches for real hardware. These use the Adafruit DHT library with the sensor data on pin 7, and include the `isnan()` check. I did not run them in Tinkercad, so they are included as extras for anyone who has a DHT11.

## Visuals
**LCD test: "Hello, Robotics!" and the seconds counter**

![LCD test](../Projects/Images/Weather%20Station%20Day%2023%20%28LCD%20test%29.PNG)

**Temperature and humidity on the LCD (TMP36 and potentiometer)**

![Temp and humidity](../Projects/Images/Weather%20Station%20Day%2023%20%28temp%20and%20humidity%29.PNG)

**Too hot: "HOT" message and the red LED on**

![Too hot LED](../Projects/Images/Weather%20Station%20Day%2023%20%28too%20hot%20LED%29.PNG)

**Fahrenheit mode after pressing the button**

![Fahrenheit](../Projects/Images/Weather%20Station%20Day%2023%20%28fahrenheit%29.PNG)

**Final circuit**

![Final circuit](../Projects/Images/Weather%20Station%20Day%2023%20%28final%20circuit%29.PNG)

## Files
- [Day23_LCD_Test.ino](../Projects/Day-23/Day23_LCD_Test.ino) – LCD test (Exercise 2)
- [Day23_Weather_Station_TMP36.ino](../Projects/Day-23/Day23_Weather_Station_TMP36.ino) – final weather station used in Tinkercad (TMP36 and potentiometer, LED alert and °C/°F button)
- [Day23_DHT11_Serial_Test.ino](../Projects/Day-23/Day23_DHT11_Serial_Test.ino) – DHT11 Serial Monitor test for real hardware (not run in Tinkercad)
- [Day23_Weather_Station_DHT11.ino](../Projects/Day-23/Day23_Weather_Station_DHT11.ino) – full weather station using a DHT11 on pin 7 (not run in Tinkercad)
- [Weather Station Day 23.brd](../Projects/Day-23/Weather%20Station%20Day%2023.brd) – Tinkercad circuit file

## What I Learned
- The LCD needs six signal wires in 4-bit mode (RS, E and D4–D7), plus power, ground and the backlight, which needs a 220 Ω resistor.
- Overwriting old text with trailing spaces gives a cleaner display than calling `lcd.clear()` on every update.
- `millis()` lets the display refresh every 2 seconds while the button is still checked all the time.
- A real DHT11 should only be read about every 2 seconds, and its readings should be checked with `isnan()` before they are shown.
- When a part is missing from the simulator, a stand-in sensor lets me test the same logic.

## Conclusion
Day 23 took me from raw sensor values to a readable display. The weather station reads temperature and humidity, shows them on the LCD, warns when it is too hot, and lets the user switch units with a button. I reached the level-up stage with both the comfort alert and the °C/°F toggle.
