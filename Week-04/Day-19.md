
# Day 19: Smart Systems

## Overview
Today I built an automatic night light in Tinkercad Circuits using an Arduino Uno R3. A light sensor reads the surrounding brightness, the Arduino applies logic to the reading, and an LED turns on when it gets dark and off when it is bright. The goal was to apply the Sense, Think, Act pattern that every automated physical system follows.

## Concepts Explored
- **Sense, Think, Act:** read the environment, apply logic to the reading, then control an output based on the decision.
- **LDR voltage divider:** the LDR and a 10kΩ resistor feed a changing voltage into analog pin A0, read with `analogRead()` as a value from 0 to 1023.
- **Hysteresis:** using two thresholds instead of one so the LED does not flicker when the light level hovers near the boundary.
- **Calibration:** choosing thresholds from measured dark and bright readings instead of guessing.
- **Non-blocking timing:** using `millis()` so the Serial Monitor prints once per second while the system keeps reacting quickly.

## What I Built
The circuit connects the LDR voltage divider to analog pin A0 and an LED with a 220Ω resistor to digital pin 13.

The sketch reads the LDR continuously and decides the LED state with two thresholds taken from my earlier calibration (dark = 54, bright = 974):
- The LED turns **ON** when the reading falls below **400**.
- The LED turns **OFF** when the reading rises above **600**.
- Between 400 and 600 the LED keeps its last state.

The Serial Monitor prints the current LDR reading and LED state once every second, for example `LDR: 54 | LED: ON`.

## Visuals

**Demo video:** [Smart Night Light Day 19 (demo).mp4](../Projects/Day-19/Smart%20Night%20Light%20Day%2019%20%28demo%29.mp4)

The demo shows the cause and effect clearly: when the sensor is set to dark the LED turns on, and when it is set back to bright the LED turns off.

## Files
- [Day19_Automatic_Night_Light.ino](../Projects/Day-19/Day19_Automatic_Night_Light.ino)
- [Smart Night Light Day 19 (demo).mp4](../Projects/Day-19/Smart%20Night%20Light%20Day%2019%20%28demo%29.mp4)

## What I Learned
- Every smart system can be broken into three layers: sense, think and act.
- Two thresholds are more stable than one, because the gap between them stops rapid toggling.
- Thresholds based on measured readings make the system switch reliably at the right light level.
- Serial output once per second is a simple way to confirm what the system is reading and deciding.

## Conclusion
Day 19 turned a sensor and an LED into a complete automatic system. The night light now reacts to the light level on its own and stays stable near the switching point, which is the same principle behind thermostats and other automated devices.
