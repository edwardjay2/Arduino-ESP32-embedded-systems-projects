#include <Arduino.h>

const int maxRecords = 10;

//=== ECU CRITICAL COUNTERS ===
int engineCriticalFaults = 0;
int brakeCriticalFaults = 0;
int transCriticalFaults = 0;

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

            Serial.println("HIGH PRIORITY FAULT DETECTED");

            // ENGINE ECU COUNTER
            if(ecu == "ENGINE"){

                engineCriticalFaults++;

                Serial.print("ENGINE CRITICAL COUNT: ");
                Serial.println(engineCriticalFaults);

                if(engineCriticalFaults > 2){

                    Serial.println("ENGINE ECU ISOLATED FROM NETWORK");
                }
            }

            // BRAKE ECU COUNTER
            else if(ecu == "BRAKE"){

                brakeCriticalFaults++;

                Serial.print("BRAKE CRITICAL COUNT: ");
                Serial.println(brakeCriticalFaults);

                if(brakeCriticalFaults > 2){

                    Serial.println("BRAKE ECU ISOLATED FROM NETWORK");
                }
            }

            // TRANS ECU COUNTER
            else if(ecu == "TRANS"){

                transCriticalFaults++;

                Serial.print("TRANS CRITICAL COUNT: ");
                Serial.println(transCriticalFaults);

                if(transCriticalFaults > 2){

                    Serial.println("TRANS ECU ISOLATED FROM NETWORK");
                }
            }
        }

    } else {

        Serial.println("MEMORY FULL");
    }
}

//=== DECODE FAULTS ===
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

//=== SHOW HISTORY ===
void showHistory(){

    Serial.println("\n=== ECU EVENT HISTORY ===");

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

//=== SETUP ===
void setup(){

    Serial.begin(9600);

    Serial.println("=== ADVANCED ECU ISOLATION SYSTEM ===");
}

//=== LOOP ===
void loop(){

    // SIMULATED HIGH PRIORITY ENGINE EVENTS
    sendFault("ENGINE",101,3);
    sendFault("ENGINE",101,3);
    sendFault("BRAKE",201,2);
    sendFault("ENGINE",101,3);

    delay(2000);

    showHistory();

    while(true); // stop


}
