#include <Arduino.h>

const int maxRecords = 10;
int criticalFaults = 0;

//=== ECU CRITICAL COUNTERS ===
int engineCriticalFaults = 0;
int brakeCriticalFaults = 0;
int transCriticalFaults = 0;
int suspensionCriticalFaults = 0;
int doorCriticalFaults = 0;
int tireCriticalFaults = 0;

//=== FAULT STRUCT ===
struct FaultMessage{

  String ecu;
  int code;
  int priority;
};

//=== MEMORY ===
FaultMessage logBuffer[maxRecords];

int logIndex = 0;

//=== SEND FAULT ===
void sendFault(String ecu, int code, int priority){

  if(logIndex < maxRecords){

    // STORE EVENT
    logBuffer[logIndex].ecu = ecu;
    logBuffer[logIndex].code = code;
    logBuffer[logIndex].priority = priority;

    logIndex++;

    // DISPLAY EVENT
    Serial.print("FAULT FROM: ");
    Serial.print(ecu);

    Serial.print(" | CODE: ");
    Serial.print(code);

    Serial.print(" | PRIORITY: ");
    Serial.println(priority);

    //=== HIGH PRIORITY CHECK ===
    if(priority == 3){

      criticalFaults++;

      Serial.println("HIGH PRIORITY FAULT DETECTED");

      Serial.print("TOTAL CRITICAL FAULTS: ");
      Serial.println(criticalFaults);

      // SAFE MODE
      if(criticalFaults > 5){

        Serial.println("TRUCK ENTERING SAFE MODE");
      }

      //=== ENGINE ECU ===
      if(ecu == "ENGINE"){

        engineCriticalFaults++;

        Serial.print("ENGINE CRITICAL COUNT: ");
        Serial.println(engineCriticalFaults);

        if(engineCriticalFaults > 2){

          Serial.println("ENGINE ECU ISOLATED FROM NETWORK");
        }
      }

      //=== BRAKE ECU ===
      else if(ecu == "BRAKE"){

        brakeCriticalFaults++;

        Serial.print("BRAKE CRITICAL COUNT: ");
        Serial.println(brakeCriticalFaults);

        if(brakeCriticalFaults > 2){

          Serial.println("BRAKE ECU ISOLATED FROM NETWORK");
        }
      }

      //=== TRANS ECU ===
      else if(ecu == "TRANS"){

        transCriticalFaults++;

        Serial.print("TRANS CRITICAL COUNT: ");
        Serial.println(transCriticalFaults);

        if(transCriticalFaults > 2){

          Serial.println("TRANS ECU ISOLATED FROM NETWORK");
        }
      }

      //=== SUSPENSION ECU ===
      else if(ecu == "SUSPENSION"){

        suspensionCriticalFaults++;

        Serial.print("SUSPENSION CRITICAL COUNT: ");
        Serial.println(suspensionCriticalFaults);

        if(suspensionCriticalFaults > 2){

          Serial.println("SUSPENSION ECU ISOLATED FROM NETWORK");
        }
      }

      //=== DOOR ECU ===
      else if(ecu == "DOOR ECU"){

        doorCriticalFaults++;

        Serial.print("DOOR ECU CRITICAL COUNT: ");
        Serial.println(doorCriticalFaults);

        if(doorCriticalFaults > 2){

          Serial.println("DOOR ECU ISOLATED FROM NETWORK");
        }
      }

      //=== TIRE ECU ===
      else if(ecu == "TIRE ECU"){

        tireCriticalFaults++;

        Serial.print("TIRE ECU CRITICAL COUNT: ");
        Serial.println(tireCriticalFaults);

        if(tireCriticalFaults > 2){

          Serial.println("TIRE ECU ISOLATED FROM NETWORK");
        }
      }
    }
  }

  else{

    Serial.println("MEMORY FULL");
  }
}

//=== DECODE FAULT ===
void decodeFault(String ecu, int code){

  if(ecu == "ENGINE" && code == 101){
    Serial.println("ENGINE OVERHEAT");
  }

  else if(ecu == "BRAKE" && code == 201){
    Serial.println("LOW BRAKE PRESSURE");
  }

  else if(ecu == "TRANS" && code == 301){
    Serial.println("GEAR SLIP");
  }

  else if(ecu == "SUSPENSION" && code == 401){
    Serial.println("AIR LEAK");
  }

  else if(ecu == "DOOR ECU" && code == 501){
    Serial.println("DOOR FAILURE");
  }

  else if(ecu == "TIRE ECU" && code == 601){
    Serial.println("LOW TIRE PRESSURE");
  }
}

//=== PRIORITY CHECK ===
void checkPriority(int priority){

  if(priority == 1){
    Serial.println("LOW PRIORITY");
  }

  else if(priority == 2){
    Serial.println("MEDIUM PRIORITY");
  }

  else if(priority == 3){
    Serial.println("HIGH PRIORITY");
  }
}

//=== SHOW FULL HISTORY ===
void showHistory(){

  Serial.println("\n=== FULL ECU HISTORY ===");

  for(int i = 0; i < logIndex; i++){

    Serial.print("ECU: ");
    Serial.print(logBuffer[i].ecu);

    Serial.print(" | CODE: ");
    Serial.print(logBuffer[i].code);

    Serial.print(" | PRIORITY: ");
    Serial.println(logBuffer[i].priority);

    checkPriority(logBuffer[i].priority);

    decodeFault(
      logBuffer[i].ecu,
      logBuffer[i].code
    );

    Serial.println("-------------------");
  }
}

//=== SHOW ONLY CRITICAL EVENTS ===
void showCriticalFaults(){

  Serial.println("\n=== CRITICAL EVENTS ONLY ===");

  for(int i = 0; i < logIndex; i++){

    // FILTER ONLY PRIORITY 3
    if(logBuffer[i].priority == 3){

      Serial.print("ECU: ");
      Serial.print(logBuffer[i].ecu);

      Serial.print(" | CODE: ");
      Serial.print(logBuffer[i].code);

      Serial.print(" | PRIORITY: ");
      Serial.println(logBuffer[i].priority);

      checkPriority(logBuffer[i].priority);

      decodeFault(
        logBuffer[i].ecu,
        logBuffer[i].code
      );

      Serial.println("-------------------");
    }
  }
}

//=== CLEAR HISTORY ===
void clearHistory(){

  logIndex = 0;

  criticalFaults = 0;

  engineCriticalFaults = 0;
  brakeCriticalFaults = 0;
  transCriticalFaults = 0;
  suspensionCriticalFaults = 0;
  doorCriticalFaults = 0;
  tireCriticalFaults = 0;

  Serial.println("FAULT HISTORY CLEARED");
}

//=== SETUP ===
void setup(){

  Serial.begin(9600);

  Serial.println("=== MINI EUROPEAN TRUCK CENTRAL GATEWAY ===");
}

//=== LOOP ===
void loop(){

  // SIMULATED EVENTS
  sendFault("ENGINE", 101, 3);
  sendFault("ENGINE", 101, 3);
  sendFault("BRAKE", 201, 3);
  sendFault("ENGINE", 101, 3);
  sendFault("BRAKE", 201, 3);
  sendFault("BRAKE", 201, 3);

  sendFault("TRANS", 301, 2);
  sendFault("SUSPENSION", 401, 2);
  sendFault("DOOR ECU", 501, 1);
  sendFault("TIRE ECU", 601, 2);

  delay(2000);

  // SHOW ALL EVENTS
  showHistory();

  // SHOW ONLY CRITICAL EVENTS
  showCriticalFaults();

  // CLEAR SYSTEM
  clearHistory();

  while(true);
}
