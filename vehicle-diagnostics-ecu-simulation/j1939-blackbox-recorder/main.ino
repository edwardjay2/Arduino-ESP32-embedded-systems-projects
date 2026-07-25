#include <Arduino.h>
#include <EEPROM.h>

const int MAX_MESSAGES = 20; // a recorder can store 20 J1939 messages
const int MAX_FAULTS = 10; // a recorder can store 10 DTCs 

const int MESSAGE_COUNT_ADDR = 0; //[EEPROM Address] Read README.md from 2864 - 2905 to understand better
const int FAULT_COUNT_ADDR = 1; //[EEPROM Address] Read README.md from 2864 - 2905 to understand better

//==================== J1939 MESSAGE ====================
struct J1939Message{

  int pgn;
  int spn;
  int value;
};

//==================== DTC ====================
struct DTC{

  int spn;
  int fmi;
};

//==================== STORAGE ====================
J1939Message messageHistory[MAX_MESSAGES];

DTC faultHistory[MAX_FAULTS];

int messageIndex = 0;

int activeFaults = 0;

//==================== EVENT COUNTERS ====================
int warningEvents = 0;
int overheatEvents = 0;
int lowFuelEvents = 0;
int networkTrafficEvents = 0;

//==================== STORE MESSAGE ====================
void storeMessage(J1939Message msg){

  if(messageIndex < MAX_MESSAGES){

    messageHistory[messageIndex] = msg;

    messageIndex++;
  }
}

//==================== STORE FAULT ====================
void storeFault(int spn,int fmi){

  if(activeFaults < MAX_FAULTS){

    faultHistory[activeFaults].spn = spn;

    faultHistory[activeFaults].fmi = fmi;

    activeFaults++;
  }
}

//==================== SAVE TO EEPROM ====================
void saveRecorder(){

  EEPROM.write(MESSAGE_COUNT_ADDR,messageIndex);

  EEPROM.write(FAULT_COUNT_ADDR,activeFaults);

  EEPROM.commit();

  Serial.println("BLACKBOX SAVED");
}

//==================== LOAD FROM EEPROM ====================
void loadRecorder(){

  messageIndex = EEPROM.read(MESSAGE_COUNT_ADDR);

  activeFaults = EEPROM.read(FAULT_COUNT_ADDR);

  Serial.println("BLACKBOX RESTORED");
}

//==================== DECODE MESSAGE ====================
void decodeJ1939(J1939Message msg){

  storeMessage(msg);

  // ENGINE TEMP
  if(msg.pgn == 65262 &&
     msg.spn == 110){

      Serial.print("ENGINE TEMP: ");
      Serial.println(msg.value);

      if(msg.value > 100){

        Serial.println("ENGINE OVERHEAT");

        overheatEvents++;

        warningEvents++;

        storeFault(110,0);
      }
  }

  // FUEL LEVEL
  else if(msg.pgn == 65276 &&
          msg.spn == 96){

      Serial.print("FUEL LEVEL: ");
      Serial.println(msg.value);

      if(msg.value < 20){

          Serial.println("LOW FUEL");

          lowFuelEvents++;

          warningEvents++;

          storeFault(96,1);
      }
  }

  if(messageIndex > 10){

      networkTrafficEvents++;

      Serial.println("NETWORK TRAFFIC HIGH");
  }
}

//==================== SHOW HISTORY ====================
void showMessages(){

  Serial.println("\n===== MESSAGE HISTORY =====");

  for(int i=0;i<messageIndex;i++){

      Serial.print("PGN: ");

      Serial.print(messageHistory[i].pgn);

      Serial.print(" SPN: ");

      Serial.print(messageHistory[i].spn);

      Serial.print(" VALUE: ");

      Serial.println(messageHistory[i].value);
  }
}

//==================== SHOW FAULTS ====================
void showFaults(){

  Serial.println("\n===== ACTIVE FAULTS =====");

  for(int i=0;i<activeFaults;i++){

      Serial.print("SPN: ");

      Serial.print(faultHistory[i].spn);

      Serial.print(" FMI: ");

      Serial.println(faultHistory[i].fmi);
  }
}

//==================== SHOW EVENTS ====================
void showEvents(){

  Serial.println("\n===== BLACKBOX EVENTS =====");

  Serial.print("Warning Events: ");

  Serial.println(warningEvents);

  Serial.print("Overheat Events: ");

  Serial.println(overheatEvents);

  Serial.print("Low Fuel Events: ");

  Serial.println(lowFuelEvents);

  Serial.print("Network Traffic Events: ");

  Serial.println(networkTrafficEvents);

  if(activeFaults > 5){

      Serial.println();

      Serial.println("FLEET VEHICLE REQUIRES IMMEDIATE SERVICE");
  }
}

//==================== SETUP ====================
void setup(){

  Serial.begin(9600);

  EEPROM.begin(512);

  loadRecorder();

  J1939Message coolant = {65262,110,110};

  J1939Message fuel = {65276,96,15};

  // Simulate fleet traffic
  for(int i=0;i<6;i++){

      decodeJ1939(coolant);
  }

  for(int i=0;i<6;i++){

      decodeJ1939(fuel);
  }

  saveRecorder();

  showMessages();

  showFaults();

  showEvents();
}

//==================== LOOP ====================
void loop(){

}
