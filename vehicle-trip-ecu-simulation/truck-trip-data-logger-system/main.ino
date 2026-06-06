#include <Arduino.h>
#include <EEPROM.h>

const int EEPROM_SIZE = 32;

int recordIndex = 0;
const int maxRecords = 5;

int tripCount = 0;

// Memory layout
// Address 0 -> recordIndex
// Address 1 -> tripCount
// Address 2+ -> records

void setup() {
Serial.begin(9600);
EEPROM.begin(EEPROM_SIZE);

Serial.println("=== SMART TRUCK TRIP COUNT AND DISTANCE ===");
Serial.println("S = SAVE TRIP");
Serial.println("R = READ SAVED TRIP");
Serial.println("C = RESET");

recordIndex = EEPROM.read(0);
tripCount   = EEPROM.read(1);
}

void loop() {
if (Serial.available() > 0) {

char input = Serial.read();    

if (input == 'S') {    

  if (recordIndex < maxRecords) {    

    int address = 2 + (recordIndex * 2);    

    tripCount++;      
    int distance = 120;    

    EEPROM.write(address, tripCount);    
    EEPROM.write(address + 1, distance);    

    recordIndex++;    

    EEPROM.write(0, recordIndex);    
    EEPROM.write(1, tripCount);    

    EEPROM.commit();    

    Serial.print("Saved Record: ");    
    Serial.println(recordIndex);    

  } else {    
    Serial.println("MEMORY FULL");    
  }    

} else if (input == 'R') {    

  for (int i = 0; i < recordIndex; i++) {    

    int address = 2 + (i * 2);    

    int savedTrip = EEPROM.read(address);    
    int distance  = EEPROM.read(address + 1);    

    Serial.print("Trip ");    
    Serial.print(savedTrip);    
    Serial.print(" -> Distance: ");    
    Serial.print(distance);    
    Serial.println(" km");    
  }    

} else if (input == 'C') {    

  recordIndex = 0;    
  tripCount = 0;    

  EEPROM.write(0, 0);    
  EEPROM.write(1, 0);    
  EEPROM.commit();    

  Serial.println("All records cleared");    
}

}
}
