#include <Arduino.h>

const int maxRecords = 10;

//=== FAULT STRUCT ====
struct FaultMessage{

  String ecu;
  int code;
  int priority;
};

//==== MEMORY ====
FaultMessage logBuffer[maxRecords];

int logIndex = 0;

//=== SEND FAULT ===
void sendFault(String ecu, int code, int priority){
  if(logIndex < maxRecords){
    logBuffer[logIndex].ecu = ecu;
    logBuffer[logIndex].code = code;
    logBuffer[logIndex].priority = priority;

    logIndex++;

    Serial.print("FAULT FROM");
    Serial.print(ecu);

    Serial.print(" CODE ");
    Serial.print(code);

    Serial.print(" PRIORITY ");
    Serial.print(priority);
  }
}

//== DECODE FAULTS ===
void decodeFault(String ecu, int code){
  if(ecu == "ENGINE" && code == 101){
    Serial.println("ENGINE OVERHEAT");
  }

  if(ecu == "BRAKE" && code == 201){
    Serial.println("LOW BRAKE PRESSURE");
  }
  
  if(ecu == "TRANS" && code == 301){
    Serial.println("GEARBOX SLIP");
  }
}

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

void showCriticalFaults(){
  Serial.println("\n=== CRITICAL FAULTS ONLY ===");
  
  for(int i = 0; i < logIndex; i++){
    
    if(logBuffer[i].priority == 3){
      
      Serial.print("ECU: ");
      Serial.print(logBuffer[i].ecu);

      Serial.print(" | CODE: ");
      Serial.print(logBuffer[i].code);

      Serial.print(" | PRIORITY: ");
      Serial.print(logBuffer[i].priority);


      checkPriority(logBuffer[i].priority);

      decodeFault(
        logBuffer[i].ecu,
        logBuffer[i].code

        // === CRITICAL FAULTS ONLY ===

      //  ECU: ENGINE | CODE: 101 | PRIORITY: 3
      //  HIGH PRIORITY
      //  ENGINE OVERHEAT
      //  -------------------

      //  ECU: TRANS | CODE: 301 | PRIORITY: 3
      //  HIGH PRIORITY
      //  GEARBOX SLIP
      //  -------------------

      );

      Serial.println("-------------------");
                    
    }
  }
}

void setup(){
  Serial.begin(9600);

  Serial.println("=== SMART TRUCK PRIORITY ECU SYSTEM ===");
}

void loop(){

  //SIMULATION FAULT EVENTS
  sendFault("ENGINE", 101, 3);
  sendFault("BRAKE", 201, 2 );
  sendFault("TRANS", 301, 3);

  delay(2000);

  showCriticalFaults();

  while (true); // stop

}
