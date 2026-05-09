#include <Arduino.h>
#include <EEPROM.h>

const int memorySize = 32;
const int serviceAddress = 1;

int serviceCount = 0;

void setup() {
  Serial.begin(9600);

  EEPROM.begin(memorySize);

  serviceCount = EEPROM.read(serviceAddress);

  Serial.println("=== ECU SERVICE RESET SYSTEM ===");
  Serial.println("Type R to reset service count");
}

void loop() {

  if (Serial.available() > 0) {

    char input = Serial.read();

    if (input == 'R') {

      serviceCount = 0;

      EEPROM.write(serviceAddress, serviceCount);
      EEPROM.commit();

      Serial.println("SERVICE COUNT RESET COMPLETE");
      Serial.print("Current Count: ");
      Serial.println(serviceCount);
    }
  }
}
