#include <Arduino.h>

const int coolantPin = 2;
const int brakePin = 4;
const int doorPin = 5;
const int pressurePin = 6;

const int warningOutput = 3;

void setup() {
  pinMode(coolantPin, INPUT_PULLUP);
  pinMode(brakePin, INPUT_PULLUP);
  pinMode(doorPin, INPUT_PULLUP);
  pinMode(pressurePin, INPUT_PULLUP);

  pinMode(warningOutput, OUTPUT);
}

void loop() {

  bool coolantFault = (digitalRead(coolantPin) == LOW);
  bool brakeFault = (digitalRead(brakePin) == LOW);
  bool doorFault = (digitalRead(doorPin) == LOW);
  bool pressureFault = (digitalRead(pressurePin) == LOW);

  bool systemFault =
      coolantFault ||
      brakeFault ||
      doorFault ||
      pressureFault;

  digitalWrite(warningOutput, systemFault);
}
