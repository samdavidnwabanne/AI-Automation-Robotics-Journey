// Day 25 - Stage 2: test the outputs and the button alone
// Green LED pin 8, red LED pin 12, buzzer pin 4, button pin 2.
const int BTN_PIN    = 2;
const int BUZZER_PIN = 4;
const int GREEN_LED  = 8;
const int RED_LED    = 12;

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  bool pressed = (digitalRead(BTN_PIN) == LOW);
  digitalWrite(GREEN_LED, pressed ? LOW : HIGH);   // green on while idle
  digitalWrite(RED_LED, pressed ? HIGH : LOW);     // red on while pressed
  if (pressed) tone(BUZZER_PIN, 1000);             // beep while pressed
  else noTone(BUZZER_PIN);
  Serial.println(pressed ? "Button: PRESSED" : "Button: released");
  delay(100);
}
