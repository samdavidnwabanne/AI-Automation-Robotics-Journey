
# Project Report: Heat & Intruder Alarm

**Name:** Heat & Intruder Alarm

**What it does:** It sounds an alarm when the temperature gets too high, and when the light level drops while the system is armed.

## Block diagram
![Block diagram](Day25_Block_Diagram.png)

## Parts list
| Part | Quantity | Pin |
|---|---|---|
| Arduino Uno R3 | 1 | n/a |
| Breadboard | 1 | n/a |
| TMP36 temperature sensor | 1 | A1 |
| LDR (light sensor) | 1 | A0 |
| 10 kΩ resistor (LDR divider) | 1 | A0 to GND |
| Push button | 1 | pin 2 (INPUT_PULLUP) |
| Piezo buzzer | 1 | pin 4 |
| Green LED | 1 | pin 8 |
| Red LED | 1 | pin 12 |
| 220 Ω resistors (one per LED) | 2 | in series with each LED |
| Jumper wires | several | n/a |

## How it works
The Arduino reads the TMP36 and the LDR, and checks the button. If the temperature reaches the heat limit, the heat alarm turns on and gives a steady tone, and it only turns off again after the temperature falls a few degrees lower. When the system is armed with the button (green LED on), a drop in light below the light limit starts the intruder alarm, a two-tone siren that stays on until the button is pressed. The red LED lights during either alarm.

## Limits I chose
| Value | Chosen | Why |
|---|---|---|
| Heat alarm on | 40 °C | (fill in after testing) |
| Heat alarm off | 38 °C | (fill in after testing) |
| Light limit | 500 | (fill in after testing) |

## One problem I hit and how I fixed it
(Fill in after building: one real problem and how you fixed it.)
