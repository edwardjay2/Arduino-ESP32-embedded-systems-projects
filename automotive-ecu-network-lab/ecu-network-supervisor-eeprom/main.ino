#include <Arduino.h>
#include <EEPROM.h>

const int maxECUs = 6;

const int EEPROM_BASE = 0;
const int OFFLINE_COUNTER_ADDRESS = 50;
const int RECONNECT_COUNTER_ADDRESS = 60;

//===== GLOBAL COUNTERS =====
int offlineECUCount = 0;
int reconnectCount = 0;

//===== BLACKBOX LOCK =====
bool blackboxLocked = false;

//===== ECU STATUS STRUCT =====
struct ECUStatus{

  String ecu;
  bool online;
  int missedMessages;
  bool critical;
};

//===== NETWORK MEMORY =====
ECUStatus network[maxECUs];

int ecuCount = 0;

//===== REGISTER ECU =====
void registerECU(String ecu, bool critical){

  network[ecuCount].ecu = ecu;

  network[ecuCount].online = true;

  network[ecuCount].missedMessages = 0;

  network[ecuCount].critical = critical;

  ecuCount++;

  Serial.print(ecu);

  Serial.println(" REGISTERED TO NETWORK");
}

//===== SAVE ECU STATES =====
void saveECUStates(){

  int address = EEPROM_BASE;

  for(int i = 0; i < ecuCount; i++){

    EEPROM.write(
      address++,
      network[i].missedMessages
    );

    EEPROM.write(
      address++,
      network[i].online
    );
  }

  EEPROM.commit();

  Serial.println(
    "ECU STATES SAVED TO EEPROM"
  );
}

//===== LOAD ECU STATES =====
void loadECUStates(){

  int address = EEPROM_BASE;

  for(int i = 0; i < ecuCount; i++){

    network[i].missedMessages =
      EEPROM.read(address++);

    network[i].online =
      EEPROM.read(address++);
  }

  Serial.println(
    "ECU STATES LOADED FROM EEPROM"
  );
}

//===== SAVE OFFLINE COUNTER =====
void saveOfflineCount(){

  EEPROM.write(
    OFFLINE_COUNTER_ADDRESS,
    offlineECUCount
  );

  EEPROM.commit();

  Serial.println(
    "OFFLINE EVENT COUNT SAVED"
  );
}

//===== LOAD OFFLINE COUNTER =====
void loadOfflineCount(){

  offlineECUCount =
    EEPROM.read(
      OFFLINE_COUNTER_ADDRESS
    );

  Serial.println(
    "OFFLINE EVENT COUNT LOADED"
  );
}

//===== SAVE RECONNECT COUNTER =====
void saveReconnectCount(){

  EEPROM.write(
    RECONNECT_COUNTER_ADDRESS,
    reconnectCount
  );

  EEPROM.commit();

  Serial.println(
    "RECONNECT EVENT COUNT SAVED"
  );
}

//===== LOAD RECONNECT COUNTER =====
void loadReconnectCount(){

  reconnectCount =
    EEPROM.read(
      RECONNECT_COUNTER_ADDRESS
    );

  Serial.println(
    "RECONNECT EVENT COUNT LOADED"
  );
}

//===== RECEIVE HEARTBEAT =====
void receiveHeartbeat(String ecu){

  for(int i = 0; i < ecuCount; i++){

    if(network[i].ecu == ecu){

      //===== BLACKBOX LOCK MODE =====
      if(
        blackboxLocked &&
        network[i].critical == false
      ){

        Serial.print(ecu);

        Serial.println(
          " BLOCKED BY BLACKBOX LOCK"
        );

        return;
      }

      //===== ECU RECOVERY =====
      if(network[i].online == false){

        Serial.print(ecu);

        Serial.println(
          " RECONNECTED TO NETWORK"
        );

        // RESET MISSED COUNTER
        network[i].missedMessages = 0;

        Serial.println(
          "MISSED MESSAGE COUNTER RESET"
        );

        reconnectCount++;

        Serial.print(
          "TOTAL RECONNECT EVENTS: "
        );

        Serial.println(reconnectCount);

        saveReconnectCount();

        saveECUStates();
      }

      // ECU BACK ONLINE
      network[i].online = true;

      Serial.print(
        "HEARTBEAT RECEIVED FROM "
      );

      Serial.println(ecu);
    }
  }
}

//===== WATCHDOG CHECK =====
void watchdogCheck(){

  int offlineNow = 0;

  Serial.println(
    "\n=== WATCHDOG STATUS ==="
  );

  for(int i = 0; i < ecuCount; i++){

    network[i].missedMessages++;

    Serial.print(network[i].ecu);

    Serial.print(" MISSED: ");

    Serial.println(
      network[i].missedMessages
    );

    //===== ECU TIMEOUT =====
    if(network[i].missedMessages > 3){

      // PREVENT REPEATED COUNTS
      if(network[i].online == true){

        network[i].online = false;

        offlineECUCount++;

        Serial.print(
          "TOTAL OFFLINE EVENTS: "
        );

        Serial.println(
          offlineECUCount
        );

        saveOfflineCount();

        saveECUStates();
      }

      Serial.print(network[i].ecu);

      Serial.println(
        " LOST COMMUNICATION"
      );

      Serial.println(
        "NETWORK FAILURE DETECTED"
      );

      Serial.println(
        "BACKUP MODE ACTIVATED"
      );
    }

    // COUNT OFFLINE ECUs
    if(network[i].online == false){

      offlineNow++;
    }
  }

  //===== EMERGENCY MODE =====
  if(offlineNow > 3){

    Serial.println(
      "CENTRAL GATEWAY ENTERING EMERGENCY NETWORK MODE"
    );
  }

  //===== BLACKBOX LOCK =====
  if(offlineECUCount > 8){

    blackboxLocked = true;

    Serial.println(
      "BLACKBOX RECORDER LOCKED"
    );

    Serial.println(
      "ONLY CRITICAL ECUs ALLOWED ONLINE"
    );
  }
}

//===== SHOW NETWORK =====
void showNetwork(){

  Serial.println(
    "\n=== NETWORK STATUS ==="
  );

  for(int i = 0; i < ecuCount; i++){

    Serial.print("ECU: ");

    Serial.print(network[i].ecu);

    Serial.print(" | ONLINE: ");

    Serial.print(network[i].online);

    Serial.print(" | MISSED: ");

    Serial.print(
      network[i].missedMessages
    );

    Serial.print(" | CRITICAL: ");

    Serial.println(
      network[i].critical
    );
  }
}

//===== SHOW FAILED ECUs =====
void showFailedECUs(){

  Serial.println(
    "\n=== FAILED ECUs ==="
  );

  for(int i = 0; i < ecuCount; i++){

    if(network[i].online == false){

      Serial.print("ECU: ");

      Serial.print(network[i].ecu);

      Serial.println(
        " | FAILED"
      );
    }
  }
}

//===== SETUP =====
void setup(){

  Serial.begin(9600);

  EEPROM.begin(512);

  //===== REGISTER ECUs =====
  registerECU("ENGINE", true);

  registerECU("BRAKE", true);

  registerECU("TRANS", true);

  registerECU("SUSPENSION", false);

  registerECU("DOOR ECU", false);

  registerECU("TIRE ECU", false);

  //===== LOAD SAVED DATA =====
  loadECUStates();

  loadOfflineCount();

  loadReconnectCount();

  //===== INITIAL HEARTBEATS =====
  receiveHeartbeat("ENGINE");

  receiveHeartbeat("BRAKE");

  receiveHeartbeat("TRANS");
}

//===== LOOP =====
void loop(){

  // FORCE FAILURES
  watchdogCheck();
  watchdogCheck();
  watchdogCheck();
  watchdogCheck();

  // SHOW NETWORK STATUS
  showNetwork();

  // SHOW FAILED ECUs
  showFailedECUs();

  delay(3000);

  // ECU RECOVERY
  receiveHeartbeat("TRANS");
 
  receiveHeartbeat("SUSPENSION");

  receiveHeartbeat("DOOR ECU");

  // SHOW UPDATED STATUS
  showNetwork();

  while(true);
}
