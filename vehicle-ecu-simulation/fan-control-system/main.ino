#include <Arduino.h>

const int pressurePin = 2;
const int tempPin = 4;
const int fanOutput = 3;

bool fanState = false;

void setup() {
  pinMode(pressurePin, INPUT_PULLUP);
  pinMode(tempPin, INPUT_PULLUP);
  pinMode(fanOutput, OUTPUT);
}

void loop() {
  int lowPressure = digitalRead(pressurePin);
  int tempHot = digitalRead(tempPin);

  if (tempHot == LOW || lowPressure == LOW) {
    digitalWrite(fanOutput, HIGH); // ECU: activate fan warning
    fanState = true;
  } 
  else {
    digitalWrite(fanOutput, LOW);
    fanState = false;
  }
}
