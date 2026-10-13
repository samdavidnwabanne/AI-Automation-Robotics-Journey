# Day 17: Inputs & Sensors

## Overview
Today I built an automatic light sensor using an LDR (Light Dependent Resistor) and an Arduino Uno in Tinkercad Circuits. The LED turns on by itself when the light level drops below a threshold. Instead of guessing the threshold, I measured the sensor's readings in dark and bright conditions first and calculated the cut-off from them.

## Concepts Explored
- **LDR (Light Dependent Resistor):** its resistance changes with light. It is high in darkness and low in bright light.
- **Voltage divider:** the LDR and a 10kΩ resistor split the 5V supply. As the LDR's resistance changes, the voltage at the middle point changes with it.
- **analogRead():** reads that voltage on pin A0 and returns a value between 0 (0V) and 1023 (5V).
- **Threshold:** the cut-off value the code compares the reading against. It should sit between the real dark and bright readings, not at the centre of 0 to 1023.
- **Serial Monitor:** printing the readings every 500ms made it possible to see the sensor values and calibrate the circuit.

## What I Built
The circuit in Tinkercad:
- 5V → LDR → A0 → 10kΩ resistor → GND (voltage divider)
- Pin 7 → 220Ω resistor → LED anode (long leg), LED cathode (short leg) → GND

**Step 1: Measure the range.** I ran a sketch that prints the LDR value to the Serial Monitor and moved the light slider on the photoresistor to both ends:

| Condition | Reading |
|-----------|---------|
| Dark (sensor covered) | 54 |
| Bright | 974 |

**Step 2: Set the threshold.** The midpoint is (54 + 974) / 2 = **514**. The final sketch turns the LED on when the reading falls below 514 and off otherwise.

**Step 3: Test.** Moving the slider slowly from bright to dark switched the LED on automatically once the reading dropped below the threshold, and moving it back switched the LED off.

### Final code
```cpp
int ldrPin = A0;
int ledPin = 7;

int threshold = 514;   // (54 + 974) / 2

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int lightValue = analogRead(ldrPin);
  Serial.println(lightValue);

  if (lightValue < threshold) {
    digitalWrite(ledPin, HIGH);   // dark: LED ON
  } else {
    digitalWrite(ledPin, LOW);    // bright: LED OFF
  }

  delay(500);
}
```

## Visuals
Final circuit (threshold = 514, dark reading, LED on):

![Final circuit](../Projects/Images/LDR%20Light%20Sensor%20Day%2017%20%28final%20circuit%29.PNG)

Dark value (54):

![Dark value](../Projects/Images/LDR%20Light%20Sensor%20Day%2017%20%28dark%20value%29.PNG)

Bright value (974):

![Bright value](../Projects/Images/LDR%20Light%20Sensor%20Day%2017%20%28bright%20value%29.PNG)

## Files
- [Day17_LDR_Light_Sensor.ino](../Projects/Day-17/Day17_LDR_Light_Sensor.ino) (final sketch, threshold 514)
- [Day17_LDR_Measure_Readings.ino](../Projects/Day-17/Day17_LDR_Measure_Readings.ino) (sketch used to measure the dark and bright values)
- [LDR Light Sensor Day 17.brd](../Projects/Day-17/LDR%20Light%20Sensor%20Day%2017.brd) (Tinkercad circuit export)

## What I Learned
A threshold should come from measured data. The readings of 54 and 974 are specific to this circuit, so a number guessed in advance would have switched the LED at the wrong light level. Printing the values to the Serial Monitor made the calibration straightforward.

## Conclusion
This task showed how a sensor can drive an output automatically: light level in, voltage change through the divider, a comparison in code, and the LED responding. Measuring first and then deciding the threshold made the result reliable.
