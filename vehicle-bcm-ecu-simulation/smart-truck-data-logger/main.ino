#include <Arduino.h>
#include <EEPROM.h>

const int EEPROM_SIZE = 32;
int recordIndex = 0;   // keeps track of next free position
const int maxRecords = 5;

void setup() {
    Serial.begin(9600);
    EEPROM.begin(EEPROM_SIZE);

    Serial.println("SMART TRUCK DATA LOGGER");
    Serial.println("S = Save Record");
    Serial.println("R = Read Records");
    Serial.println("C = Clear Memory");
}

void loop() {
    if (Serial.available() > 0) {
        char input = Serial.read();

        // ================= SAVE RECORD =================
        if (input == 'S') {

            if (recordIndex < maxRecords) {
                int address = recordIndex * 2;

                // Example sensor values
                int temperature = 45 + recordIndex * 5;
                int pressure = 30 - recordIndex * 2;

                EEPROM.write(address, temperature);
                EEPROM.write(address + 1, pressure);
                EEPROM.commit();

                Serial.print("Saved Record ");
                Serial.println(recordIndex + 1);

                recordIndex++;
            } 
            else {
                Serial.println("MEMORY FULL");
            }
        }

        // ================= READ ALL RECORDS =================
        else if (input == 'R') {

            Serial.println("=== SAVED RECORDS ===");

            for (int i = 0; i < recordIndex; i++) {
                int address = i * 2;

                int temp = EEPROM.read(address);
                int pressure = EEPROM.read(address + 1);

                Serial.print("Record ");
                Serial.print(i + 1);
                Serial.print(" -> Temp: ");
                Serial.print(temp);
                Serial.print("  Pressure: ");
                Serial.println(pressure);

                // Warning checks
                if (temp > 40) {
                    Serial.println("WARNING: OVERHEAT");
                }

                if (pressure < 28) {
                    Serial.println("WARNING: LOW PRESSURE");
                }
            }

            Serial.println("--------------------");
        }

        // ================= CLEAR MEMORY =================
        else if (input == 'C') {

            for (int i = 0; i < EEPROM_SIZE; i++) {
                EEPROM.write(i, 0);
            }
            EEPROM.commit();

            recordIndex = 0;

            Serial.println("MEMORY CLEARED");
        }
    }
}
