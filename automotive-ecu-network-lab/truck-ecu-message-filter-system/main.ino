#include <Arduino.h>

const int maxRecords = 10;
int faultCount = 0;

//===== STRUCT =====
struct FaultMessage{
    String ecu;
    int code;
};

//===== MEMORY =====
FaultMessage logBuffer[maxRecords];
int logIndex = 0;

//===== SEND FAULT =====
void sendFault(String ecu, int code){

    if(logIndex < maxRecords){

        logBuffer[logIndex].ecu = ecu;
        logBuffer[logIndex].code = code;

        logIndex++;
        faultCount++;
    }
}

//===== DECODE =====
void decodeFault(String ecu, int code){

    if(ecu == "ENGINE" && code == 101){
        Serial.println("ENGINE OVERHEAT");
    }

    else if(ecu == "BRAKE" && code == 201){
        Serial.println("LOW BRAKE PRESSURE");
    }

    else if(ecu == "TRANS" && code == 301){
        Serial.println("GEARBOX SLIP");
    }
}

//===== SHOW ENGINE FAULTS ONLY =====
void showEngineFaults(){

    Serial.println("\n=== ENGINE FAULTS ONLY ===");

    for(int i = 0; i < logIndex; i++){

        // filter only ENGINE records
        if(logBuffer[i].ecu == "ENGINE"){

            Serial.print("ECU: ");
            Serial.print(logBuffer[i].ecu);

            Serial.print(" | CODE: ");
            Serial.print(logBuffer[i].code);

            Serial.print(" => ");

            decodeFault(
                logBuffer[i].ecu,
                logBuffer[i].code
            );
        }
    }
}

//===== SETUP =====
void setup(){

    Serial.begin(9600);

    sendFault("ENGINE",101);
    sendFault("BRAKE",201);
    sendFault("TRANS",301);
  

    showEngineFaults();
}

void loop(){

}
