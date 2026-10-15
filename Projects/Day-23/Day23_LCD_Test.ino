// Day 23 - Exercise 2: LCD test
// Line 1: "Hello, Robotics!"   Line 2: seconds since start
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);   // RS, E, D4, D5, D6, D7

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Hello, Robotics!");
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  lcd.print(millis() / 1000);
  lcd.print(" s   ");                    // trailing spaces wipe old digits
}
