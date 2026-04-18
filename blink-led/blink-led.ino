#include <Arduino.h>

void setup() {
    pinMode(2, OUTPUT); // Set built-in LED pin as output
}

void loop() {
    digitalWrite(2, HIGH); // Turn LED on
    delay(1000);            // Wait 1 second
    digitalWrite(2, LOW);   // Turn LED off
    delay(1000);            // Wait 1 second
}

======================== DUAL LED SEQUENCE CONTROL =========================
#include <Arduino.h>

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  digitalWrite(2, HIGH);
  delay(1000);

  digitalWrite(3, HIGH);
  delay(2000);

  digitalWrite(2, LOW);
  delay(1000);

  digitalWrite(3, LOW);
  delay(2000);
}
