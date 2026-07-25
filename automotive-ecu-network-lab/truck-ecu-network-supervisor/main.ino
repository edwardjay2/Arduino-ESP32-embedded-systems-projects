 #include <Arduino.h>

const int maxECUs = 6;

int totalHeartbeats = 0;

//=== ECU STATUS ===
struct ECUStatus{

    String ecu;
    bool online;
    int missedMessages;
};

//=== NETWORK MEMORY ===
ECUStatus network[maxECUs];

int ecuCount = 0;

//=== REGISTER ECU ===
void registerECU(String ecu){

    network[ecuCount].ecu = ecu;
    network[ecuCount].online = true;
    network[ecuCount].missedMessages = 0;

    ecuCount++;

    Serial.print(ecu);
    Serial.println(" REGISTERED TO NETWORK");
}

//=== RECEIVE HEARTBEAT ===
void receiveHeartbeat(String ecu){

    for(int i = 0; i < ecuCount; i++){

        if(network[i].ecu == ecu){

            // ECU RECOVERY
            if(network[i].online == false){

                Serial.print(ecu);
                Serial.println(" RECONNECTED TO NETWORK");
            }

            // RESET WATCHDOG
            network[i].missedMessages = 0;

            network[i].online = true;

            Serial.print("HEARTBEAT RECEIVED FROM ");
            Serial.println(ecu);

            totalHeartbeats++;

            Serial.print("TOTAL HEARTBEATS: ");
            Serial.println(totalHeartbeats);
        }
    }
}

//=== WATCHDOG CHECK ===
void watchdogCheck(){

    Serial.println("\n=== WATCHDOG STATUS ===");

    int offlineECUs = 0;

    for(int i = 0; i < ecuCount; i++){

        network[i].missedMessages++;

        Serial.print(network[i].ecu);

        Serial.print(" MISSED: ");
        Serial.println(network[i].missedMessages);

        // ECU TIMEOUT
        if(network[i].missedMessages > 2){

            network[i].online = false;

            offlineECUs++;

            Serial.print(network[i].ecu);
            Serial.println(" LOST COMMUNICATION");

            Serial.println("NETWORK FAILURE DETECTED");

            Serial.println("BACKUP MODE ACTIVATED");
        }
    }

    //=== SEVERE CONDITION ===
    if(offlineECUs > 3){

        Serial.println(
          "CENTRAL GATEWAY ENTERING EMERGENCY NETWORK MODE"
        );
    }
}

//=== SHOW NETWORK ===
void showNetwork(){

    Serial.println("\n=== NETWORK STATUS ===");

    for(int i = 0; i < ecuCount; i++){

        Serial.print("ECU: ");
        Serial.print(network[i].ecu);

        Serial.print(" | ONLINE: ");
        Serial.println(network[i].online);
    }
}

//=== SHOW OFFLINE ECUs ===
void showOfflineECUs(){

    Serial.println("\n=== OFFLINE ECUs ===");

    for(int i = 0; i < ecuCount; i++){

        if(network[i].online == false){

            Serial.print("ECU: ");
            Serial.print(network[i].ecu);

            Serial.println(" | OFFLINE");
        }
    }
}

//=== SETUP ===
void setup(){

    Serial.begin(9600);

    Serial.println(
      "=== MINI EUROPEAN TRUCK NETWORK SUPERVISOR ==="
    );

    // REGISTER ECUs
    registerECU("ENGINE");
    registerECU("BRAKE");
    registerECU("TRANS");
    registerECU("SUSPENSION");
    registerECU("DOOR ECU");
    registerECU("TIRE ECU");
}

//=== LOOP ===
void loop(){

    // ACTIVE ECUs
    receiveHeartbeat("ENGINE");
    receiveHeartbeat("BRAKE");

    // TRANS reconnect simulation
    receiveHeartbeat("TRANS");

    watchdogCheck();

    showNetwork();

    showOfflineECUs();

    delay(3000);
