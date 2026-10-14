# Day 22: DC Motor Control & Relay Switching

## Overview
Today I built a transistor-driven DC motor with potentiometer speed control, then added a relay-switched lamp. I worked in Tinkercad Circuits with an Arduino Uno R3 and wrote one sketch for each exercise, ending with a temperature-controlled fan.

## Concepts Explored
- **Why a transistor is needed:** an Arduino pin supplies only about 20 mA, but a motor needs much more. An NPN transistor acts as the switch, so a small current into the base (through a 1kΩ resistor) lets a large current flow from collector to emitter.
- **Flyback diode:** a diode across the motor (and across the relay coil), with the striped end toward 5V, absorbs the voltage spike when the load switches off.
- **PWM speed control:** `analogWrite(pin, 0 to 255)` sets the motor speed on a pin marked with `~`, and `map()` converts the potentiometer reading (0–1023) into a speed value.
- **Relay:** an electromagnet that moves a switch. It has COM, NO and NC contacts and keeps the Arduino separate from the load. A relay is switched with `digitalWrite()`, never `analogWrite()`.
- **Active LOW and HIGH:** `RELAY_ON` and `RELAY_OFF` constants make the relay level easy to change in one place.
- **State-change method:** each button press toggles a state only when the button goes from HIGH to LOW.

## What I Built
The circuit uses these connections:
- Motor transistor base on pin 5 through a 1kΩ resistor, with a flyback diode across the motor
- Motor button on pin 2 (INPUT_PULLUP) and a motor-on LED on pin 8 through 220Ω
- Potentiometer on A0
- Relay coil transistor base on pin 4 through a 1kΩ resistor, with a diode across the coil
- Lamp button on pin 3, and a lamp LED switched by the relay contacts through a 220Ω resistor
- TMP36 temperature sensor on A1 for the level-up

I wrote a separate sketch for each exercise:
1. **Motor button:** each press toggles the motor on and off, and the LED shows when the motor is on.
2. **Motor speed:** the potentiometer sets the motor speed, and the Serial Monitor prints the speed as a percentage from 0 to 100.
3. **Motor and relay lamp:** the final sketch combines the motor, speed control and a button that switches the relay lamp. The relay pin is set to its OFF level before `pinMode()` so it does not click on at start-up.
4. **Temperature fan (level up):** the motor stays off below 25 °C and reaches full speed at 35 °C, using `map()` and `constrain()`.

## Visuals

**Motor button**

![Motor button](../Projects/Images/Motor%20Relay%20Day%2022%20%28motor%20button%29.PNG)

**Motor speed**

![Motor speed](../Projects/Images/Motor%20Relay%20Day%2022%20%28motor%20speed%29.PNG)

**Relay lamp**

![Relay lamp](../Projects/Images/Motor%20Relay%20Day%2022%20%28relay%20lamp%29.PNG)

**Temperature fan**

![Temperature fan](../Projects/Images/Motor%20Relay%20Day%2022%20%28temp%20fan%29.PNG)

**Final circuit**

![Final circuit](../Projects/Images/Motor%20Relay%20Day%2022%20%28final%20circuit%29.PNG)

## Files
- [Day22_Motor_Button.ino](../Projects/Day-22/Day22_Motor_Button.ino)
- [Day22_Motor_Speed.ino](../Projects/Day-22/Day22_Motor_Speed.ino)
- [Day22_Motor_Relay_Lamp.ino](../Projects/Day-22/Day22_Motor_Relay_Lamp.ino)
- [Day22_Temp_Fan.ino](../Projects/Day-22/Day22_Temp_Fan.ino)
- [Motor Relay Day 22.brd](../Projects/Day-22/Motor%20Relay%20Day%2022.brd)

## What I Learned
- A transistor lets a small Arduino signal control a much larger load, and a diode across the load protects the circuit.
- PWM changes motor speed smoothly, and `map()` turns a sensor reading into a usable output value.
- A relay isolates the load from the Arduino, so it must be driven with its own transistor and flyback diode.
- Building one sketch per exercise made it easy to test each part before combining them.

## Conclusion
Day 22 moved from switching small signals to controlling real loads. The motor, the speed control and the relay lamp now work together in one circuit, and the temperature fan shows how a sensor can drive a motor automatically.
