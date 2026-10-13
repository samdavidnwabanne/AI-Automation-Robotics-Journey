// Day 21 - Exercise 4: Test the buzzer alone
// Buzzer positive -> pin 7, negative -> GND
// tone(pin, frequency, duration) plays a note; noTone(pin) stops it.
// A higher frequency gives a higher pitch.

const int buzzerPin = 7;

void setup() {
  tone(buzzerPin, 1000, 200);   // one short beep: 1000 Hz for 200 ms
  delay(1000);
}

void loop() {
  tone(buzzerPin, 800);         // low pitch
  delay(500);
  tone(buzzerPin, 1500);        // high pitch
  delay(500);
  noTone(buzzerPin);            // silence
  delay(1000);
}
