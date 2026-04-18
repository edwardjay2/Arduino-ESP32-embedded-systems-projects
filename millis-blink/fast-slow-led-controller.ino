#include <Arduino.h>

//Timing intervals
unsigned long fastInterval = 300;
unsigned long slowInterval = 1000;

//Variables
unsigned long previousTime = 0;
unsigned long currentInterval = fastInterval;

bool ledState = false;
bool systemOn = true;

void setup() {
  Serial.begin(9600);
  Serial.println("Smart LED Controller Started");
  Serial.println("Press 1 = FAST, 2 = SLOW, 0 = OFF");
}


void loop() {
  unsigned long currentMillis = millis();

  //  HANDLE USER INPUT
  if(Serial.available() > 0) {
    char input = Serial.read();

    if (input == '1') {
      currentInterval = fastInterval;
      systemOn = true;
      Serial.println("Mode: FAST");
    }
    else if (input == '2') {
      currentInterval = slowInterval;
      systemOn = true;
      Serial.println("Mode: SLOW");
    }
    else if (input == '0') {
      systemOn = false;
      Serial.println("LED OFF");
    }
  }

  //  NON-BLOCKING LED CONTROL
  if (systemOn && (currentMillis - previousTime >= currentInterval)) {
    previousTime = currentMillis;
    ledState = !ledState;

    Serial.print("LED is");
    Serial.println(ledState ? "ON" : "OFF");
  }
}
