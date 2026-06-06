#include <Arduino.h>
#include <EEPROM.h>

const int EEPROM_SIZE = 32;

int recordIndex = 0;
const int maxRecords = 3;

// Memory layout:
// Address 0 -> recordIndex
// Address 1+ -> fault history

void setup() {
  Serial.begin(9600);
  EEPROM.begin(EEPROM_SIZE);

  Serial.println("=== FAULT TRUCK HISTORY LOGGER ===");
  Serial.println("O = SAVE FAULT (OVERHEAT)");
  Serial.println("D = DISPLAY FAULTS");

  recordIndex = EEPROM.read(0);
}

void loop() {

  if (Serial.available() > 0) {

    char input = Serial.read();

    // ================= SAVE FAULT =================
    if (input == 'O') {

      if (recordIndex < maxRecords) {

        int address = 1 + recordIndex;

        int faultCode = 101; // OVERHEAT

        EEPROM.write(address, faultCode);
        EEPROM.commit();

        recordIndex++;

        EEPROM.write(0, recordIndex);
        EEPROM.commit();

        Serial.print("Saved Fault Record: ");
        Serial.println(recordIndex);
      }
      else {
        Serial.println("MEMORY FULL");
      }
    }

    // ================= DISPLAY FAULTS =================
    else if (input == 'D') {

      Serial.println("=== FAULT HISTORY ===");

      for (int i = 0; i < recordIndex; i++) {

        int address = 1 + i;
        int fault = EEPROM.read(address);

        Serial.print("Fault Code: ");
        Serial.println(fault);

        if (fault == 101) {
          Serial.println("OVERHEAT");
        }
      }
    }
  }
}
