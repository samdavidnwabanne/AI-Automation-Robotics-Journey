# Day 29: Water-Level Indicator and Automatic Pump Controller

## Overview
Today I built a water-level indicator and automatic pump controller in Tinkercad Circuits. An ultrasonic sensor mounted above the tank measures the distance down to the water surface, and the Arduino uses that distance to decide whether to switch a pump on or off through a relay. A red LED shows a LOW level and a green LED shows a FULL level.

## How the System Works
**Senses.** The ultrasonic sensor sits above the water and measures the distance to the surface. A larger distance means a lower water level, and a smaller distance means a higher level. The sketch also turns the distance into an estimated level in percent, with the FULL distance as 100 % and the distance to the bottom of the tank as 0 %.

**Decides.** Two thresholds turn the distance into a decision:
- At or beyond the **LOW** distance, the water is low, so the pump turns on.
- At or closer than the **FULL** distance, the water is full, so the pump turns off.
- Between the two, the pump keeps its current state, which stops it switching on and off rapidly near a limit.
- A reading of 0 means no echo, so the sketch ignores it.

**Switches the pump.** The Arduino pin does not drive the pump directly. It controls a relay through a transistor, and the relay switches the pump's own power circuit. This keeps the pump's circuit separate from the Arduino's control signal, which protects the microcontroller.

## Thresholds
| Value | Distance from sensor | Meaning |
|---|---|---|
| FULL | 5 cm | At or closer than this, the tank is full and the pump turns off |
| LOW | 20 cm | At or farther than this, the tank is low and the pump turns on |
| EMPTY | 30 cm | The bottom of the tank, which is 0 % |

**How I chose them:** I treated the tank as 30 cm deep from the sensor to the bottom, so a reading of 30 cm is 0 % and a reading of 5 cm is 100 %. I set FULL at 5 cm so the water never reaches the sensor, and LOW at 20 cm, which leaves a 15 cm gap between the two so the pump does not keep switching near a limit. I then checked the values by moving the distance slider on the sensor in Tinkercad and reading the Serial Monitor.

## Test Results
I used the DC motor as the pump and the sensor's distance slider as the water level, since Tinkercad has no real water.

| Slider setting | Distance shown | Level | Status | Pump |
|---|---|---|---|---|
| 25 cm | 25 cm | 20 % | LOW | ON |
| 19.8 cm | 19 cm | 44 % | NORMAL | ON |
| 5.7 cm | 5 cm | 100 % | FULL | OFF |
| 4 cm | 4 cm | 100 % | FULL | OFF |

**What the results show:**
- At 25 cm the water is low, so the pump turns on.
- At 19 cm the status is NORMAL, but the pump is still ON. This is the gap between the thresholds at work: the pump keeps its last state until the water reaches FULL.
- At 5 cm the tank is full, so the pump turns off.
- At 4 cm the level stays at 100 %, because the code limits the level to 0 to 100 %.
- The slider showed 19.8 cm and 5.7 cm, but the Serial Monitor showed 19 and 5. The sketch stores the distance as a whole number, so it drops the decimals.

## Components and Pins
| Part | Connection |
|---|---|
| Ultrasonic sensor | SIG to pin 7, with 5V and GND |
| Relay (through a transistor driver) | pin 4 |
| DC motor (the pump) | switched by the relay contacts (a diode D1 sits across the relay coil) |
| Red LED (LOW) | pin 8 through 220 Ω |
| Green LED (FULL) | pin 12 through 220 Ω |

## Visuals
**Circuit**

![Circuit](../Projects/Images/Water%20Pump%20Day%2029%20%28circuit%29.PNG)

**Code**

![Code](../Projects/Images/Water%20Pump%20Day%2029%20%28code%29.PNG)

**Serial Monitor: distance, level and pump state**

![Serial Monitor](../Projects/Images/Water%20Pump%20Day%2029%20%28serial%20monitor%29.png)

## Files
- [Day29_Water_Level_Pump.ino](../Projects/Day-29/Day29_Water_Level_Pump.ino) – the water-level indicator and pump controller

## What I Learned
- An ultrasonic sensor above the water gives a larger distance for a lower water level.
- Thresholds turn a measurement into a control decision, and a gap between them stops the pump from flickering.
- A relay lets a small Arduino signal switch the pump's separate power circuit.
- Code should ignore a reading of 0, which means no echo, instead of acting on it.
- Thresholds should be tested with real readings, not guessed.
- The sketch stores the distance as a whole number, so decimals from the sensor are dropped.

## Conclusion
Day 29 combined sensing, decision-making and switching in one useful system. The sensor measures, two thresholds decide, and the relay switches the pump, with the LEDs showing the state.
