#include <Arduino.h>

const int maxRecords = 20;

int totalMessages = 0;

//===== CAN MESSAGE =====
struct CANMessage{

  int id;
  int data;
};

//===== HISTORY STORAGE =====
CANMessage history[maxRecords];

int msgIndex = 0;

//===== STORE MESSAGE =====
void storeMessage(CANMessage msg){

  if(msgIndex < maxRecords){

    history[msgIndex] = msg;

    msgIndex++;

    // Count message when received
    totalMessages++;
  }
}

//===== DECODE MESSAGE =====
void decodeMessage(CANMessage msg){

  // ENGINE
  if(msg.id == 0x101){

    Serial.print("ENGINE TEMP: ");
    Serial.println(msg.data);

    if(msg.data > 100){

      Serial.println("ENGINE OVERHEAT WARNING");
    }
  }

  // BRAKE
  else if(msg.id == 0x201){

    Serial.print("BRAKE PRESSURE: ");
    Serial.println(msg.data);
  }

  // TRANS
  else if(msg.id == 0x301){

    Serial.print("CURRENT GEAR: ");
    Serial.println(msg.data);
  }

  // SUSPENSION
  else if(msg.id == 0x401){

    Serial.print("SUSPENSION STATUS: ");
    Serial.println(msg.data);
  }

  // DOOR ECU
  else if(msg.id == 0x501){

    Serial.print("DOOR STATUS: ");
    Serial.println(msg.data);
  }

  // TIRE ECU
  else if(msg.id == 0x601){

    Serial.print("TIRE PRESSURE: ");
    Serial.print(msg.data);
    Serial.println(" PSI");

    if(msg.data < 30){

      Serial.println("LOW TIRE PRESSURE WARNING");
    }
  }

  Serial.println();
}

//===== SHOW WARNINGS ONLY =====
void showWarnings(){

  Serial.println("\n=== WARNING MESSAGES ===");

  for(int i = 0; i < msgIndex; i++){

    if(history[i].id == 0x101 &&
       history[i].data > 100){

      Serial.println("ENGINE OVERHEAT WARNING");
    }

    if(history[i].id == 0x601 &&
       history[i].data < 30){

      Serial.println("LOW TIRE PRESSURE WARNING");
    }
  }
}

//===== SHOW FULL HISTORY =====
void showHistory(){

  Serial.println("\n=== FULL CAN HISTORY ===");

  for(int i = 0; i < msgIndex; i++){

    decodeMessage(history[i]);
  }

  Serial.print("TOTAL CAN MESSAGES: ");
  Serial.println(totalMessages);

  if(totalMessages > 15){

    Serial.println(
      "CENTRAL GATEWAY ENTERING BUS PROTECTION MODE"
    );
  }
  else if(totalMessages > 10){

    Serial.println(
      "CAN BUS TRAFFIC HIGH"
    );
  }
}

//===== SETUP =====
void setup(){

  Serial.begin(9600);

  CANMessage engineMsg;
  engineMsg.id = 0x101;
  engineMsg.data = 110;

  CANMessage brakeMsg;
  brakeMsg.id = 0x201;
  brakeMsg.data = 120;

  CANMessage transMsg;
  transMsg.id = 0x301;
  transMsg.data = 4;

  CANMessage suspensionMsg;
  suspensionMsg.id = 0x401;
  suspensionMsg.data = 3;

  CANMessage doorMsg;
  doorMsg.id = 0x501;
  doorMsg.data = 1;

  CANMessage tireMsg;
  tireMsg.id = 0x601;
  tireMsg.data = 20;

  // Store messages
  storeMessage(engineMsg);
  storeMessage(brakeMsg);
  storeMessage(transMsg);
  storeMessage(suspensionMsg);
  storeMessage(doorMsg);
  storeMessage(tireMsg);

  // Extra traffic
  for(int i = 0; i < 10; i++){

    storeMessage(engineMsg);
  }

  showWarnings();

  showHistory();
}

//===== LOOP =====
void loop(){

}
