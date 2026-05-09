#include <Arduino.h>
#include <EEPROM.h>

int count = 0;   // service count variable

void setup() {
  Serial.begin(9600);
  EEPROM.begin(32);

  // Read saved count from EEPROM address 1
  count = EEPROM.read(1);

  Serial.println("=== SERVICE COUNTER SYSTEM ===");
  Serial.println("C = increase count");
  Serial.println(" R = reset count");
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();

    // Increase count
    if (input == 'C') {
      count++;

      EEPROM.write(1, count);
      EEPROM.commit();

      Serial.print("Service Count: ");
      Serial.println(count);
    }

    // Reset count
    if (input == 'R') {
      count = 0;

      EEPROM.write(1, count);
      EEPROM.commit();

      Serial.println("SERVICE COUNT RESET");
      Serial.print("Service Count: ");
      Serial.println(count);
    }
  }
}
