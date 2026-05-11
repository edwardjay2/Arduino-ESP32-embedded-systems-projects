#include <Arduino.h>
#include <EEPROM.h>

const int EEPROM_SIZE = 32;
int tripCount = 0;
int recordIndex = 0;
int maxRecords = 5;

// Memory layout
// Address 0 -> recordIndex
// Address 1 -> tripCount
// Address 2+ -> records


void setup(){
  Serial.begin(9600);
  EEPROM.begin(EEPROM_SIZE);
  Serial.println("=== SMART TRUCK TRIP MEMORY SYSTEM ===");
  Serial.println("S = SAVE TRIP COUNT");
  Serial.println("R = RETRIEVE SAVED TRIP COUNT");

  recordIndex = EEPROM.read(0);
  tripCount = EEPROM.read(1);


}

void loop(){
  if(Serial.available () > 0){
    char input = Serial.read();

    if(input == 'S'){
      if(recordIndex < maxRecords){
      int  address = 2 + (recordIndex * 3);

      tripCount++;
      int distance = 100 + tripCount * 20;
      int fuelUsed = 10 + tripCount * 2;

      EEPROM.write(address, tripCount);
      EEPROM.write(address + 1, distance);
      EEPROM.write(address + 2, fuelUsed);

      recordIndex++;

      EEPROM.write(0, recordIndex);
      EEPROM.write(1, tripCount);

      EEPROM.commit();

      Serial.print("Save Record");
      Serial.println(recordIndex);

      if(tripCount > 10){
        Serial.println("SERVICE REQUIRED");
      }


      } else {
        Serial.println("MEMORY FULL");

      
      }
    } else
    if(input == 'R'){
      for(int i = 0; i < recordIndex; i++){
        int address = 2 + (i * 3);

        int savedTrip = EEPROM.read(address);
        int distance = EEPROM.read(address + 1);
        int fuel = EEPROM.read(address + 2);

        Serial.print("Trip");
        Serial.print(savedTrip);
        Serial.print("-> Distance: ");
        Serial.print(distance);
        Serial.print(" Fuel Used: ");
        Serial.println(fuel);

      }
    } else 
    if(input == 'C'){
      for (int i = 0; i < EEPROM_SIZE; i++){
        EEPROM.write(i, 0);

      }
      EEPROM.commit();

      recordIndex = 0;
      tripCount = 0;

      Serial.println("All records cleared");

    }
  }

}
