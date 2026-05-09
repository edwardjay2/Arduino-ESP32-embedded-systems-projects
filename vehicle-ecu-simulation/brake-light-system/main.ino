#include <Arduino.h>

const int brakeSwitch = 2;
const int brakeLight = 3;

void setup() {
  pinMode(brakeSwitch, INPUT_PULLUP);
  pinMode(brakeLight, OUTPUT);
}

void loop() {
  int brakeState = digitalRead(brakeSwitch);

  if (brakeState == LOW) {
    digitalWrite(brakeLight, HIGH); // Brake applied
  } else {
    digitalWrite(brakeLight, LOW);  // Brake released
  }
}
