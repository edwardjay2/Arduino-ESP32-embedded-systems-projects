#include <Arduino.h>
#include <EEPROM.h>

const int EEPROM_SIZE = 32;

int faultCount = 0;

void setup() {
  Serial.begin(9600);
  EEPROM.begin(EEPROM_SIZE);

  Serial.println("=== FAULT COUNTER SYSTEM ===");
  Serial.println("P = LOW PRESSURE");
  Serial.println("D = DISPLAY FAULTS");

  faultCount = EEPROM.read(0);
}

void loop() {

  if (Serial.available() > 0) {

    char input = Serial.read();

    if (input == 'P') {

      faultCount++;

      EEPROM.write(0, faultCount);   // fault count
      EEPROM.write(1, 102);          // fault code (LOW PRESSURE)

      EEPROM.commit();

      Serial.println("LOW PRESSURE SAVED");
    }

    else if (input == 'D') {

      int faults = EEPROM.read(0);
      int fault = EEPROM.read(1);

      Serial.print("Fault Count: ");
      Serial.println(faults);

      Serial.print("Last Fault Code: ");
      Serial.println(fault);

      if (fault == 102) {
        Serial.println("LOW PRESSURE");
      }
    }
  }
}
