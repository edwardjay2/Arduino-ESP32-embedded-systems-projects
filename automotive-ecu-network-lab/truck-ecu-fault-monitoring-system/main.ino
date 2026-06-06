#include <Arduino.h>

const int maxRecords = 10;
int faultCount = 0;

//===STRUCT =====
struct FaultMessage{
  String ecu;
  int code;

};

//===== MEMORY =====
FaultMessage logBuffer[maxRecords];
int logIndex = 0;

//==== SEND FAULT =====
void sendFault(String ecu, int code){
  if(logIndex < maxRecords){
    logBuffer[logIndex].ecu = ecu;
    logBuffer[logIndex].code = code;

    logIndex++;
    faultCount++;

    Serial.print("FAULT RECEIVED FROM ");
    Serial.print(ecu);
    Serial.print("CODE:");
    Serial.println(code);

    Serial.print("TOTAL FAULTS: ");
    Serial.println(faultCount);

    //WARNINGS
    if(faultCount > 8){
      Serial.println("CRITICAL VEHICLE INSPECTION REQUIRED");
    } else 
    if(faultCount >= 5){
      Serial.println("TRUCK NEEDS SERVICE");
    }
  } else {
    Serial.println("MEMORY FULL");
  }
}


//=== DECODE ===
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
  if(ecu == "SUSPENSION" && code == 401){
    Serial.println("AIR LEAK");
  }
  if(ecu == "DOOR ECU" && code == 501){
    Serial.println("DOOR FAILURE");
  }
}

//===== HISTORY =====
void showHistory(){
  Serial.println("\n===== FAULT HISTORY =====");
  for(int i = 0; i < logIndex; i++){
    Serial.print("ECU:");
    Serial.print(logBuffer[i].ecu);

    Serial.print("| CODE:");
    Serial.print(logBuffer[i].code);

    Serial.print(" => ");

    decodeFault(
      logBuffer[i].ecu,
      logBuffer[i].code
    );
  }
}

//==== CLEAR HISTORY
void clearHistory(){
  logIndex = 0;
  faultCount = 0;

  Serial.println("FAULT HISTORY CLEARED");

}

//=== SETUP ===
void setup(){
  Serial.begin(9600);

  Serial.println("=== TRUCK ECU NETWORK SIMULATION ===");

}

//===== LOOP =====
void loop(){
  
//SIMULATION FAULTS EVENTS

sendFault("ENGINE", 101);
sendFault("BRAKE", 201);
sendFault("TRANS", 301);
sendFault("SUSPENSION", 401);
sendFault("DOOR ECU", 501);

delay(2000);

showHistory();
clearHistory();

while (true);

}
