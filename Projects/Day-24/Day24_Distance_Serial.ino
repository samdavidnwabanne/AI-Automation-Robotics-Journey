// Day 24 - Exercise 2: Test distance sensing
// Tinkercad 3-pin ultrasonic sensor: one SIG pin (pin 7) does both trigger and echo.
// Move the object to 5 distances and compare with the ruler.

const int sigPin = 7;

void setup() {
  Serial.begin(9600);
}

void loop() {
  pinMode(sigPin, OUTPUT);
  digitalWrite(sigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(sigPin, HIGH);      // short pulse starts a measurement
  delayMicroseconds(5);
  digitalWrite(sigPin, LOW);

  pinMode(sigPin, INPUT);          // same pin now listens for the echo
  long duration = pulseIn(sigPin, HIGH, 30000);
  long distanceCm = duration / 58; // Tinkercad: echo time (us) / 58 = cm

  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");
  delay(500);
}
