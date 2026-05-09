#include <Arduino.h>
#include <EEPROM.h>

const int EEPROM_SIZE = 32;
int recordIndex = 0;
const int maxRecords = 5;

void setup(){
  Serial.begin(9600);
  EEPROM.begin(EEPROM_SIZE);
  Serial.println("====== SMART TRUCK BLACK BOX SYSTEM ======");
  Serial.println("S = SAVE RECORD ");
  Serial.println("R = RETRIEVE RECORDS");
  Serial.println("C = CLEAR MEMORY");


}

void loop(){
  if(Serial.available () > 0){
    char input = Serial.read();

    if(input == 'S'){
      if(recordIndex < maxRecords){
        int address = recordIndex * 3;

        int temp = 50 + recordIndex * 2;
        int pressure = 30 - recordIndex;
        int speed = 70 + recordIndex * 5;

        EEPROM.write(address, temp);
        EEPROM.write(address + 1, pressure);
        EEPROM.write(address + 2, speed);
        EEPROM.commit();

        Serial.println("Saved Record ");
        Serial.println(recordIndex + 1);

        recordIndex++;
    
      }
      else {
        Serial.println("MEMORY FULL");
      }
    } else
    //============= READ SAVED RECORDS ============
    if(input == 'R'){
      Serial.println("==== SAVED RECORDS ====");
      for(int i = 0; i < recordIndex; i++){
        int address = i * 3;

        int temp = EEPROM.read(address);
        int pressure = EEPROM.read(address + 1);
        int speed = EEPROM.read(address + 2);

        Serial.print("Record");
        Serial.print(i + 1);
        Serial.print("-> Temp: ");
        Serial.print(temp);
        Serial.print("pressure: ");
        Serial.print(pressure);
        Serial.print("Speed: ");
        Serial.println(speed);

        if(temp > 50){
          Serial.println("WARNING: OVERHEAT");

        }

        if (pressure < 20){
          Serial.println("WARNING: LOW PRESSURE");

        }
        
        if(speed > 90){
          Serial.println("WARNING: OVERSPEED");

        }


      }


    } 
    //=========== CLEAR MEMORY ===========
    else if(input == 'C'){
      Serial.println("==== ERASE MEMORY TO 0 ====");
      for(int i = 0; i < EEPROM_SIZE; i++){
        EEPROM.write(i, 0);

      }
      EEPROM.commit();

      recordIndex = 0;

      Serial.println("MEMORY CLEARED");
    }
  }

}
