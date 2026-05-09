#include <Arduino.h>

const int doorSwitch = 2;
const int buzzer = 3;

bool buzzerState = false;

void setup() {
  pinMode(doorSwitch, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  int doorState = digitalRead(doorSwitch);

  if (doorState == LOW) {
    digitalWrite(buzzer, HIGH);   // Door open warning ON
    buzzerState = true;
  } else {
    digitalWrite(buzzer, LOW);    // Door closed warning OFF
    buzzerState = false;
  }
}
