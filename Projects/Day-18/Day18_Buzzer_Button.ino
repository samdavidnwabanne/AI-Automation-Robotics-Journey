// Day 18 - Outputs & Actuators: Step 1 - buzzer sounds while the button is pressed
//
// Wiring:
//   Active buzzer: + -> pin 8, - -> GND
//   Push button:   one side -> pin 2, other side -> GND

const int buttonPin = 2;   // push button input
const int buzzerPin = 8;   // active buzzer output

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // internal pull-up: pin reads HIGH normally, LOW when pressed
  pinMode(buzzerPin, OUTPUT);        // buzzer pin sends a signal out
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {   // button pressed
    digitalWrite(buzzerPin, HIGH);       // buzzer ON
  } else {
    digitalWrite(buzzerPin, LOW);        // buzzer OFF
  }
}
