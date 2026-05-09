#include <Arduino.h>
#include <EEPROM.h>

const int EEPROM_SIZE = 32;
int recordIndex = 0;
const int maxRecords = 5;

void setup() {

  Serial.begin(9600);
  EEPROM.begin(EEPROM_SIZE);

  Serial.println("SMART TRUCK RPM SAVER AND READER");
  Serial.println("S: SAVE RECORD");
  Serial.println("R: READ RECORDS");
}

void loop() {

  if (Serial.available() > 0) {

    char input = Serial.read();

    // ========= SAVE RECORD =========
    if (input == 'S') {

      if (recordIndex < maxRecords) {

        int rpm = 1000 + recordIndex * 500;

        EEPROM.write(recordIndex, rpm);
        EEPROM.commit();

        Serial.print("Saved RPM Record ");
        Serial.println(recordIndex + 1);

        recordIndex++;
      }
      else {
        Serial.println("MEMORY FULL");
      }
    }

    // ========= READ RECORDS =========
    else if (input == 'R') {

      Serial.println("===== RPM RECORDS =====");

      for (int i = 0; i < recordIndex; i++) {

        int rpm = EEPROM.read(i);

        Serial.print("Record ");
        Serial.print(i + 1);
        Serial.print(" -> RPM: ");
        Serial.println(rpm);
      }
    }
  }
}
