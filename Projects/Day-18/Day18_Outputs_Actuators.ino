// Day 18 - Outputs & Actuators: Step 3 - button triggers servo AND buzzer
// When the button is pressed, the servo moves to 90 degrees and the buzzer
// sounds for 500 ms. Then both return to their default state (servo 0, buzzer off).
//
// Wiring:
//   Push button:   one side -> pin 2, other side -> GND
//   Active buzzer: + -> pin 8, - -> GND
//   Servo:         signal -> pin 9, power -> 5V, ground -> GND

#include <Servo.h>               // library that controls servo motors

const int buttonPin = 2;         // push button input (trigger)
const int buzzerPin = 8;         // active buzzer output
const int servoPin  = 9;         // servo signal pin

Servo myServo;                   // servo object
int triggerCount = 0;            // counts how many times the trigger worked (for testing)

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);   // pin reads HIGH normally, LOW when pressed
  pinMode(buzzerPin, OUTPUT);
  myServo.attach(servoPin);

  // default state: servo at 0 degrees, buzzer off
  myServo.write(0);
  digitalWrite(buzzerPin, LOW);

  Serial.begin(9600);                 // used to confirm every trigger in the Serial Monitor
}

void loop() {
  // trigger condition: button pressed
  if (digitalRead(buttonPin) == LOW) {
    triggerCount++;
    Serial.print("Triggered: ");
    Serial.println(triggerCount);

    // active state: servo to 90 degrees and buzzer on for 500 ms
    myServo.write(90);
    digitalWrite(buzzerPin, HIGH);
    delay(500);

    // return both outputs to their default state
    digitalWrite(buzzerPin, LOW);
    myServo.write(0);
    delay(500);                       // give the servo time to return

    // wait until the button is released so one press = one trigger
    while (digitalRead(buttonPin) == LOW) {
    }
    delay(50);                        // short debounce delay
  }
}
