# Day 21: Temperature Sensing & Alert Systems

## Overview
Today I built a temperature alarm system in Tinkercad Circuits using an Arduino Uno R3, a TMP36 temperature sensor, a buzzer, two LEDs and an arm/disarm push button. I tested the sensor and the buzzer on their own first, then combined them into a system that arms, warns and sounds an alarm based on the temperature.

## Concepts Explored
- **TMP36 sensor:** gives 10 mV per degree Celsius, with 0.5 V at 0 °C. The sketch converts the reading with `voltage = analogRead(A1) * 5.0 / 1024.0` and `tempC = (voltage - 0.5) * 100.0`.
- **Buzzer control:** `tone(pin, frequency)` and `noTone(pin)` play and stop a sound, and a higher frequency gives a higher pitch.
- **State-based design:** the alarm is a set of states (Disarmed, Armed and Alarm) remembered with the variables `armed` and `alarmOn`.
- **Latched alarm:** once triggered, the alarm stays on until the button is pressed, even if the temperature drops.
- **Non-blocking timing:** `millis()` flips the siren between two pitches without `delay()`, so the button still responds while the alarm sounds.
- **INPUT_PULLUP:** the button connects pin 2 to GND, and a press reads LOW.

## What I Built
The circuit connects:
- TMP36: 5V, signal to A1, GND
- Push button between pin 2 and GND
- Green LED on pin 8 and red LED on pin 9, each through a 220Ω resistor to GND
- Buzzer positive to pin 7 and negative to GND

I built it in three stages:
1. **Sensor test:** the sketch prints `Temperature: xx.xx C` every half second.
2. **Buzzer test:** one short beep, then two different pitches.
3. **Temperature alarm:** the first button press arms the system and turns on the green LED. While armed, slow beeps start above 28 °C. Above 30 °C the red LED turns on and the siren sounds, and it stays on until the button is pressed, which disarms everything. The Serial Monitor prints `ARMED`, `DISARMED` and `ALARM!` when the state changes.

**Level reached:** Level 1 (state messages in the Serial Monitor) and Level 3 (slow beeps above 28 °C, full siren above 30 °C).

## Sensor Readings
I moved the TMP36 slider to five positions and recorded what the Serial Monitor showed:

| Slider set to (approx.) | Serial Monitor reading |
|---|---|
| -10 °C | -8.98 °C |
| 0 °C | -0.20 °C |
| 30 °C | 31.05 °C |
| 50 °C | 51.07 °C |
| 100 °C | 99.90 °C |

The slider is hard to place on an exact value, so the settings are approximate. The readings follow the slider closely, which confirms the voltage-to-temperature formula is correct.

## Visuals

**Sensor test**

![Sensor test](../Projects/Images/Temperature%20Alarm%20Day%2021%20%28sensor%20test%29.PNG)

**Buzzer test**

![Buzzer test](../Projects/Images/Temperature%20Alarm%20Day%2021%20%28buzzer%20test%29.PNG)

**Armed**

![Armed](../Projects/Images/Temperature%20Alarm%20Day%2021%20%28armed%29.PNG)

**Alarm**

![Alarm](../Projects/Images/Temperature%20Alarm%20Day%2021%20%28alarm%29.PNG)

**Disarmed**

![Disarmed](../Projects/Images/Temperature%20Alarm%20Day%2021%20%28disarmed%29.PNG)

**Final circuit**

![Final circuit](../Projects/Images/Temperature%20Alarm%20Day%2021%20%28final%20circuit%29.PNG)

## Files
- [Day21_Temp_Sensor_Test.ino](../Projects/Day-21/Day21_Temp_Sensor_Test.ino)
- [Day21_Buzzer_Test.ino](../Projects/Day-21/Day21_Buzzer_Test.ino)
- [Day21_Temperature_Alarm.ino](../Projects/Day-21/Day21_Temperature_Alarm.ino)
- [Temperature Alarm Day 21.brd](../Projects/Day-21/Temperature%20Alarm%20Day%2021.brd)

## What I Learned
- Testing the sensor alone first proves the conversion formula before it is used in logic.
- Modeling the alarm as states makes the behavior predictable and easy to test.
- A latched alarm needs a deliberate reset, which is why the button disarms everything.
- Using `millis()` instead of `delay()` keeps the system responsive while the siren plays.

## Conclusion
Day 21 combined sensing, state logic and multiple outputs into one alarm system. The system warns early, raises the alarm above the limit, and holds it until a person resets it, which is how real alert systems behave.
