#include <Arduino.h>
#include <EEPROM.h>

const int EEPROM_SIZE = 32;
int tripCount = 0;

void setup() {
  Serial.begin(9600);
  EEPROM.begin(EEPROM_SIZE);

  Serial.println("==== SMART TRUCK TRIP COUNTER SYSTEM ====");
  Serial.println("S = STORE TRIP COUNT");
  Serial.println("R = READ SAVED TRIP");
  Serial.println("C = RESET TRIP COUNT");

  tripCount = EEPROM.read(0);
}

void loop() {

  if (Serial.available() > 0) {

    char input = Serial.read();

    if (input == 'S') {
      tripCount++;

      EEPROM.write(0, tripCount);
      EEPROM.commit();

      Serial.print("Trip Count: ");
      Serial.println(tripCount);
    }

    else if (input == 'R') {
      tripCount = EEPROM.read(0);

      Serial.print("Saved Trips: ");
      Serial.println(tripCount);
    }

    else if (input == 'C') {

      tripCount = 0;

      EEPROM.write(0, 0);
      EEPROM.commit();

      Serial.println("TRIP COUNTER RESET");
    }
  }
}
