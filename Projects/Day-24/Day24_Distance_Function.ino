// Day 24 - Exercise 3: the measuring code moved into readDistanceCm()
// loop() stays short and readable.

const int sigPin = 7;

// Takes the sensor pin, returns the distance in cm (0 = no echo).
long readDistanceCm(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  digitalWrite(pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pin, LOW);

  pinMode(pin, INPUT);
  long duration = pulseIn(pin, HIGH, 30000);
  return duration / 58;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  long distance = readDistanceCm(sigPin);
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);
}
