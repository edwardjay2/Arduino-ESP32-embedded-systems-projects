#include <Arduino.h>

void setup() {
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  int button = digitalRead(2);

  if (button == HIGH) {
    digitalWrite(3, HIGH);
  } else {
    digitalWrite(3, LOW);
  }
}

//============== VERSION 2:REVERSE(LED ON WHEN NOT PRESSED)===============
#include <Arduino.h>

void setup() {
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  int button = digitalRead(2);

  if (button == LOW) {   // Changed from HIGH to LOW
    digitalWrite(3, HIGH);  // LED ON when button NOT pressed
  } else {
    digitalWrite(3, LOW);   // LED OFF when button is pressed
  }
}
