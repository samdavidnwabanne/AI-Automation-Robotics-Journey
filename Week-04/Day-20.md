
# Day 20: Arduino Practical Challenge

## Overview
For the practical challenge I chose to build a **Smart Door** prototype in Tinkercad Circuits. An HC-SR04 ultrasonic sensor measures the distance to an object, and an Arduino Uno R3 controls a servo that "opens" the door when the object is within 30 cm and "closes" it when the object moves away.

## Concepts Explored
- **HC-SR04 ultrasonic sensor:** the Trig pin sends a pulse and the Echo pin measures how long the echo takes to return.
- **Distance calculation:** distance in cm = (`pulseIn()` duration × 0.034) / 2. The 0.034 is the speed of sound in cm/µs, and the result is divided by 2 because the sound travels to the object and back.
- **Servo control:** the `Servo` library positions the servo with `attach()` and `write()`; 0° is closed and 90° is open.
- **Threshold and edge-case testing:** checking the behavior just below, exactly at and just above the 30 cm limit.
- **Timeout handling:** `pulseIn()` with a timeout returns 0 when no echo comes back, so the sketch treats that as "no object".

## What I Built
The circuit connects the HC-SR04 to 5V and GND, Trig to pin 10 and Echo to pin 11, and the servo signal to pin 9.

The sketch is organized into clearly commented sections: pin setup, sensor reading, conditional logic and output control.
- An object at or below **30 cm** moves the servo to 90° and the door opens.
- When nothing is within range, the door waits 2 seconds and then closes. This delay stops the servo from jittering when an object sits near the boundary.
- The Serial Monitor prints the distance and door state, for example `Distance: 29.00 cm | Door: OPEN`.

While testing I found a "no echo" reading in the Serial Monitor. The cause was the Echo wire on the wrong Arduino pin. After moving it to pin 11, the readings matched the sensor.

## Visuals

**Door closed**

![Door closed](../Projects/Images/Smart%20Door%20Day%2020%20%28door%20closed%29.PNG)

**Door open**

![Door open](../Projects/Images/Smart%20Door%20Day%2020%20%28door%20open%29.PNG)

**Final circuit**

![Final circuit](../Projects/Images/Smart%20Door%20Day%2020%20%28final%20circuit%29.PNG)

**Demo video:** [Smart Door Day 20 (demo).mp4](../Projects/Day-20/Smart%20Door%20Day%2020%20%28demo%29.mp4)

## Files
- [Day20_Smart_Door.ino](../Projects/Day-20/Day20_Smart_Door.ino)
- [Smart Door Day 20 (demo).mp4](../Projects/Day-20/Smart%20Door%20Day%2020%20%28demo%29.mp4)
- [Smart Door Day 20.brd](../Projects/Day-20/Smart%20Door%20Day%2020.brd)

## What I Learned
- A wrong pin is enough to make a correct sketch fail, so checking the wiring against the code is the first debugging step.
- The Serial Monitor makes it easy to see what the sensor reads and what the system decides.
- Testing the threshold edge (29, 30 and 31 cm) shows whether the logic behaves correctly at the boundary.
- A short hold time before closing makes the door behave in a steadier, more realistic way.

## Conclusion
Day 20 brought together sensing, decision logic and a physical output in one working prototype. The Smart Door detects an object, opens, and closes again on its own, which shows how the sense, think and act pattern applies to a real-world system.
