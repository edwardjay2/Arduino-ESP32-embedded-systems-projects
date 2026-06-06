#include <Arduino.h>

const int maxRecords = 10;

//===== FAULT MEMORY ======

struct FaultMessage{
  String ecu;
  int code;
};

//simple memory buffer (like ECU log)
FaultMessage logBuffer[maxRecords];
int logIndex = 0;

//===== SEND FAULT =====
void sendFault(String ecu, int code){
  if(logIndex < maxRecords){

    logBuffer[logIndex].ecu = ecu;
    logBuffer[logIndex].code = code;

    logIndex++;

    Serial.print("FAULT RECEIVED FROM");
    Serial.print(ecu);
    Serial.print(" CODE: ");
    Serial.print(code);
  }

}

//===== DECODE =====
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

//===== DISPLAY HISTORY =====
void showHistory(){
  Serial.println("\n=== FAULT HISTORY ====");
  for(int i = 0; i < logIndex; i++){
    Serial.print("ECU:");
    Serial.print(logBuffer[i].ecu);

    Serial.print("|CODE: ");
    Serial.print(logBuffer[i].code);

    Serial.print("=>");

    decodeFault(
                logBuffer[i].ecu, 
                logBuffer[i].code
    );
  }
}

//===== CLEAR HISTORY =====
void clearHistory(){
 logIndex = 0;

 Serial.println("FAULT HISTORY CLEARED");

}
void setup(){
  Serial.begin(9600);
  Serial.print("=== TRUCK ECU NETWORK SIMULATION ===");

}

void loop(){
  //SIMULATED FAULT EVENTS
  SendFault("ENGINE", 101);
  sendFault("BRAKE", 201);
  sendFault("TRANS", 301);

  delay(2000);

  showHistory();
  clearHistory();

  while (true); //stop loop

}
