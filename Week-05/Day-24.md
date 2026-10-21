# Day 24: Distance Sensing & Servo Motor Control

## Overview
I built a smart door in Tinkercad Circuits. An ultrasonic distance sensor measures how far away an object is, and when something comes closer than 20 cm, a servo motor opens the door. A green LED shows the door is open and a red LED shows it is closed. For the level-up, I added a 2-second close delay with `millis()`, a buzzer beep when the door opens, and a lock button.

## Concepts Explored
- How an ultrasonic sensor works: it sends a burst of sound and times the echo
- Converting echo time to distance in centimetres (Tinkercad's 3-pin sensor: echo time ÷ 58)
- Using one SIG pin for both trigger and echo with `pinMode()` switching between `OUTPUT` and `INPUT`
- Ignoring a reading of 0, which means no echo
- Writing a function that takes a pin and returns a value: `long readDistanceCm(int pin)`
- Controlling a servo with the `Servo` library: `attach()` and `write(angle)`
- Mapping a potentiometer to a servo angle with `map()`
- Non-blocking timing with `millis()` instead of `delay()`
- Using `tone()` for a buzzer and a push button with `INPUT_PULLUP` to lock the door

## What I Built
**Wiring (Exercise 1).** Ultrasonic sensor SIG to pin 7 (plus 5V and GND), servo signal to pin 6 (plus 5V and GND), red LED on pin 8 and green LED on pin 12, each through a 220 Ω resistor to GND.

**Distance sensing (Exercise 2).** I printed the distance to the Serial Monitor and moved the object to five distances, then compared each reading with the ruler.

**Distance function (Exercise 3).** I moved the measuring code into `readDistanceCm(int pin)`, so `loop()` only calls the function and prints the result.

**Servo test (Exercise 4).** I tested the servo alone at 0, 90 and 180 degrees, then controlled its angle with a potentiometer on A0 using `map()`.

**Smart door (Exercise 5).** When something is closer than 20 cm and above 0, the servo moves to 90 degrees (open) and the green LED lights. Otherwise the servo returns to 0 (closed) and the red LED lights.

**Level up (Exercise 6).** I did all three options:
1. The door stays open while someone is there and closes 2 seconds after they leave, using `millis()` instead of `delay()`.
2. A short buzzer beep on pin 4 when the door opens.
3. A lock button on pin 2. While locked, the door ignores the sensor until it is unlocked.

## Sensor Readings
| Ruler distance (cm) | Sensor reading (cm) |
|---|---|
| 10 | 10 |
| 20 | 20 |
| 50 | 50 |
| 100 | 100 |
| 200 | 200 |

The readings matched the ruler at every distance I tested.

## Visuals
**Distance readings in the Serial Monitor**

![Distance reading](../Projects/Images/Smart%20Door%20Day%2024%20%28distance%20reading%29.PNG)

**Servo test**

![Servo test](../Projects/Images/Smart%20Door%20Day%2024%20%28servo%20test%29.PNG)

**Door open: object closer than 20 cm**

![Door open](../Projects/Images/Smart%20Door%20Day%2024%20%28door%20open%29.PNG)

**Door closed: object moved away**

![Door closed](../Projects/Images/Smart%20Door%20Day%2024%20%28door%20closed%29.PNG)

**Door locked: the sensor is ignored**

![Locked](../Projects/Images/Smart%20Door%20Day%2024%20%28locked%29.png)

**Final circuit**

![Final circuit](../Projects/Images/Smart%20Door%20Day%2024%20%28final%20circuit%29.PNG)

## Files
- [Day24_Distance_Serial.ino](../Projects/Day-24/Day24_Distance_Serial.ino) – distance readings in the Serial Monitor (Exercise 2)
- [Day24_Distance_Function.ino](../Projects/Day-24/Day24_Distance_Function.ino) – measuring code moved into `readDistanceCm()` (Exercise 3)
- [Day24_Servo_Positions.ino](../Projects/Day-24/Day24_Servo_Positions.ino) – servo at 0, 90 and 180 degrees (Exercise 4)
- [Day24_Servo_Pot.ino](../Projects/Day-24/Day24_Servo_Pot.ino) – servo controlled by a potentiometer (Exercise 4)
- [Day24_Smart_Door.ino](../Projects/Day-24/Day24_Smart_Door.ino) – the smart door (Exercise 5)
- [Day24_Smart_Door_Final.ino](../Projects/Day-24/Day24_Smart_Door_Final.ino) – smart door with the 2-second hold, buzzer beep and lock button (Exercise 6)
- [Smart Door Day 24.brd](../Projects/Day-24/Smart%20Door%20Day%2024.brd) – Tinkercad circuit file

## What I Learned
- Distance is calculated from the echo time, and Tinkercad's 3-pin sensor uses one SIG pin for both the trigger and the echo, with the time divided by 58.
- A reading of 0 means no echo, so the sketch has to ignore it.
- Moving code into a function with a parameter and a return value keeps `loop()` short and easy to read.
- Sensor pins must be checked against their labels. My first test read 0 because SIG and GND were swapped, and moving the wires to the right pins fixed it.
- `millis()` lets the door keep sensing while it waits to close, which `delay()` cannot do because it stops the whole program.
- A locked state is just a variable that the logic checks before it acts on the sensor.

## Conclusion
Day 24 combined a sensor, a servo, LEDs, a buzzer and a button into one working smart door. The sensor readings matched the ruler, and I reached the level-up stage with all three options: the `millis()` hold, the buzzer beep and the lock button.
