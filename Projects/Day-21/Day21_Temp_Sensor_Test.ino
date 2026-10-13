// Day 21 - Exercise 3: Test the TMP36 temperature sensor alone
// TMP36: left leg -> 5V, middle leg -> A1, right leg -> GND (flat face toward you)
// The sensor gives 10 mV per degree C, with 0.5 V at 0 degrees C.

const int tempPin = A1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int reading = analogRead(tempPin);           // 0 - 1023
  float voltage = reading * 5.0 / 1024.0;      // convert the reading to volts
  float tempC = (voltage - 0.5) * 100.0;       // convert volts to degrees Celsius

  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.println(" C");

  delay(500);                                  // print every half second
}
