# Day 18: Outputs & Actuators

## Overview
Today I worked on the output side of an Arduino system. I connected an active buzzer and a servo motor to an Arduino Uno R3 in Tinkercad Circuits, tested each one on its own, and then combined them so a single push button triggers both. The final sketch makes the system respond reliably every time the button is pressed.

## Concepts Explored
- **Actuators:** components that act on the world, such as a buzzer (sound) and a servo (movement).
- **Active buzzer:** sounds when its pin is driven HIGH with `digitalWrite()`.
- **Servo motor:** controlled with the `Servo` library using `attach()` and `write(angle)`.
- **INPUT_PULLUP:** the button uses the internal pull-up resistor, so a press reads LOW.
- **Debouncing and wait-for-release:** prevent one press from being counted more than once.

## What I Built
The circuit uses three connections on an Arduino Uno R3:
- Push button on pin 2 (other leg to GND)
- Active buzzer on pin 8 (negative leg to GND)
- Servo signal on pin 9, with 5V and GND

I built it in three stages:
1. **Buzzer and button:** the buzzer sounds while the button is held down.
2. **Servo sweep:** the servo sweeps from 0° to 180° and back using two `for` loops with a 15 ms delay.
3. **Combined actuator output:** a button press moves the servo to 90° and sounds the buzzer for 500 ms, then both return to their rest state. A wait-for-release loop and a 50 ms debounce keep each press to a single cycle, and the Serial Monitor prints a trigger count for every activation.

## Visuals

**Buzzer and button**

![Buzzer and button](../Projects/Images/Outputs%20Actuators%20Day%2018%20%28buzzer%20button%29.PNG)

**Servo sweep**

![Servo sweep](../Projects/Images/Outputs%20Actuators%20Day%2018%20%28servo%20sweep%29.PNG)

**Final circuit**

![Final circuit](../Projects/Images/Outputs%20Actuators%20Day%2018%20%28final%20circuit%29.png)

## Files
- [Day18_Buzzer_Button.ino](../Projects/Day-18/Day18_Buzzer_Button.ino)
- [Day18_Servo_Sweep.ino](../Projects/Day-18/Day18_Servo_Sweep.ino)
- [Day18_Outputs_Actuators.ino](../Projects/Day-18/Day18_Outputs_Actuators.ino)
- [Outputs Actuators Day 18.brd](../Projects/Day-18/Outputs%20Actuators%20Day%2018.brd)

## What I Learned
- Testing each output separately makes it much easier to find a wiring or code fault before combining them.
- A button needs debouncing and a wait-for-release step to give one clean trigger per press.
- Serial output is a quick way to verify that the system responds on every activation.
- Commenting the code as I write it makes the logic easier to review and reuse.

## Conclusion
Day 18 connected input and output in one working system: a button press now produces both movement and sound in a controlled, repeatable way. This gives me a solid base for building more responsive systems in the days ahead.
