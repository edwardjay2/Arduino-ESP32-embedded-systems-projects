#include <Arduino.h>

const int coolantPin = 2;
const int warningLed = 3;

void setup() {
  pinMode(coolantPin, INPUT_PULLUP);
  pinMode(warningLed, OUTPUT);
}

void loop() {
  int coolantState = digitalRead(coolantPin);

  if (coolantState == LOW) {
    digitalWrite(warningLed, HIGH); // ECU: fault detected
  } else {
    digitalWrite(warningLed, LOW);  // ECU: normal condition
  }
}
