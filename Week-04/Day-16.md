# Day 16: Introduction to Electronics & Arduino

## Overview
Today I started working with electronics and the Arduino. I wired a simple LED circuit, wrote the Blink sketch, changed the delay to make the LED blink fast and slow, and added Serial Monitor messages to confirm what the LED was doing.

## Concepts Explored
- **setup() and loop():** `setup()` runs once when the board powers on, and `loop()` runs over and over forever.
- **pinMode and digitalWrite:** `pinMode(13, OUTPUT)` makes pin 13 send out a signal. `digitalWrite(13, HIGH)` turns the LED on and `digitalWrite(13, LOW)` turns it off.
- **delay():** pauses the program for a number of milliseconds (1000 ms = 1 second).
- **Resistor:** limits the current so the LED does not burn out.
- **Serial Monitor:** `Serial.begin(9600)` and `Serial.println()` let the Arduino send messages that I can read on screen.

## What I Built
I built the circuit in Tinkercad Circuits: Arduino pin 13 → resistor → LED anode (long leg) → LED cathode (short leg) → GND.

I ran two versions of the Blink sketch:

1. **Fast blink (100 ms):** the LED turns on and off quickly.
2. **Slow blink (2000 ms):** the LED stays on for 2 seconds, then off for 2 seconds.

Both versions print "LED ON" and "LED OFF" to the Serial Monitor each time the LED changes state.

### Code (fast blink, 100 ms)
```cpp
int redLed = 13;

void setup() {
  pinMode(redLed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(redLed, HIGH);
  Serial.println("LED ON");
  delay(100);

  digitalWrite(redLed, LOW);
  Serial.println("LED OFF");
  delay(100);
}
```
For the slow version, I changed both `delay(100)` lines to `delay(2000)`.

## Visuals
Fast blink (100 ms):

![Fast blink circuit and Serial Monitor](../Projects/Images/Blinking%20Test%20Day%2016%20%40delay%28100%29.PNG)

Slow blink (2000 ms):

![Slow blink circuit and Serial Monitor](../Projects/Images/Blinking%20Test%20Day%2016%20%40delay%282000%29.PNG)

## Files
- [Day16_Blink_100ms_fast.ino](../Projects/Day16_Blink_100ms_fast.ino)
- [Day16_Blink_2000ms_slow.ino](../Projects/Day16_Blink_2000ms_slow.ino)
- [Blinking Test Day 16.brd](../Projects/Blinking%20Test%20Day%2016.brd) (Tinkercad circuit export)

## What I Learned
Changing a single number in `delay()` changes how the whole circuit behaves. The Serial Monitor also showed me what the Arduino was doing, which makes it easier to check that the code and the LED agree.

## Conclusion
This was my first hands-on step into electronics. Wiring the LED, writing the code and watching the Serial Monitor showed me how hardware and software work together.
