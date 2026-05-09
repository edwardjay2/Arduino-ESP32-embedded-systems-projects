#include <Arduino.h>
#include <EEPROM.h>

int temperature = 0;

void setup() {
  Serial.begin(9600);
  EEPROM.begin(32);

  Serial.println("TRUCK TEMPERATURE STORAGE");
  Serial.println("S: SAVE TEMPERATURE");
  Serial.println("R: PRINT TEMPERATURE");

  temperature = EEPROM.read(1);
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();

    if (input == 'S') {
      temperature = 45;
      EEPROM.write(1, temperature);
      EEPROM.commit();

      Serial.println("Temperature Saved");
    }

    else if (input == 'R') {
      temperature = EEPROM.read(1);

      Serial.print("LAST TEMP: ");
      Serial.println(temperature);

      if (temperature > 40) {
        Serial.println("WARNING: OVERHEAT");
      }
    }
  }
}
