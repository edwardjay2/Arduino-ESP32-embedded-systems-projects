#include <Arduino.h>
#include <EEPROM.h>

const int EEPROM_SIZE = 32;
int tripCount = 0;

void setup() {
  Serial.begin(9600);
  EEPROM.begin(EEPROM_SIZE);

  Serial.println("=== SMART TRUCK TRIP COUNT AND DISTANCE ===");
  Serial.println("S = SAVE TRIP");
  Serial.println("R = READ LAST TRIP");
  Serial.println("C = RESET");

  tripCount = EEPROM.read(0);
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();

    // ===== SAVE =====
    if (input == 'S') {
      tripCount++;

      int distance = 120;

      EEPROM.write(0, tripCount);
      EEPROM.write(1, distance);
      EEPROM.commit();

      Serial.print("Trip ");
      Serial.print(tripCount);
      Serial.print(" -> Distance: ");
      Serial.print(distance);
      Serial.println("km");
    }

    // ===== READ =====
    else if (input == 'R') {
      int savedTrip = EEPROM.read(0);
      int distance = EEPROM.read(1);

      Serial.print("Trip ");
      Serial.print(savedTrip);
      Serial.print(" -> Distance: ");
      Serial.print(distance);
      Serial.println("km");
    }

    // ===== RESET =====
    else if (input == 'C') {
      tripCount = 0;

      EEPROM.write(0, 0);
      EEPROM.write(1, 0);
      EEPROM.commit();

      Serial.println("TRIP RESET");
    }
  }
}
