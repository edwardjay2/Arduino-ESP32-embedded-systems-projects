#include <Arduino.h>

const int pressurePin = 2;
const int alarmLed = 3;

unsigned long previousTime = 0;
const unsigned long interval = 1000;

bool alarmState = false;

void setup() {
  pinMode(pressurePin, INPUT_PULLUP);
  pinMode(alarmLed, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  int pressureState = digitalRead(pressurePin);

  if (pressureState == LOW) { // low pressure detected
    if (currentMillis - previousTime >= interval) {
      previousTime = currentMillis;

      alarmState = !alarmState; // toggle LED
      digitalWrite(alarmLed, alarmState);
    }
  } 
  else {
    digitalWrite(alarmLed, LOW);
    alarmState = false;
  }
}
