#include <Arduino.h>
#include <EEPROM.h>

const int EEPROM_SIZE = 32;

int recordIndex = 0;
int faultCount = 0;

const int maxRecords = 20;

// Address 0 -> recordIndex
// Address 1 -> faultCount
// Address 2+ -> fault history

void setup() {

  Serial.begin(9600);
  EEPROM.begin(EEPROM_SIZE);

  Serial.println("=== SMART TRUCK ECU FAULT MEMORY SYSTEM ===");

  Serial.println("O = OVERHEAT");
  Serial.println("P = LOW PRESSURE");
  Serial.println("S = OVERSPEED");
  Serial.println("B = BRAKE FAILURE");

  Serial.println("D = DISPLAY FAULT HISTORY");

  // Recover saved data
  recordIndex = EEPROM.read(0);
  faultCount = EEPROM.read(1);
}

void loop() {

  if (Serial.available() > 0) {

    char input = Serial.read();

    int faultCode = 0;

    // DETERMINE FAULT CODE
    if (input == 'O') {
      faultCode = 101;
    }

    else if (input == 'P') {
      faultCode = 102;
    }

    else if (input == 'S') {
      faultCode = 103;
    }

    else if (input == 'B') {
      faultCode = 104;
    }

    // SAVE FAULT
    if (faultCode != 0) {

      if (recordIndex < maxRecords) {

        int address = 2 + recordIndex;

        EEPROM.write(address, faultCode);

        recordIndex++;
        faultCount++;

        EEPROM.write(0, recordIndex);
        EEPROM.write(1, faultCount);

        EEPROM.commit();

        Serial.print("Saved Fault Code: ");
        Serial.println(faultCode);

        if (faultCount > 10) {
          Serial.println("TRUCK REQUIRES INSPECTION");
        }

      } else {
        Serial.println("MEMORY FULL");
      }
    }

    // DISPLAY HISTORY
    else if (input == 'D') {

      Serial.println("=== FAULT HISTORY ===");

      for (int i = 0; i < recordIndex; i++) {

        int address = 2 + i;

        int fault = EEPROM.read(address);

        Serial.print("Fault Code: ");
        Serial.println(fault);

        if (fault == 101) {
          Serial.println("OVERHEAT");
        }

        else if (fault == 102) {
          Serial.println("LOW PRESSURE");
        }

        else if (fault == 103) {
          Serial.println("OVERSPEED");
        }
 
        else if (fault == 104) {
          Serial.println("BRAKE FAILURE");
        }
      }
    }
  }
}
