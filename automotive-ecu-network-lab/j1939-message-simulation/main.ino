#include <Arduino.h>

const int maxRecords = 20;
int totalMessages = 0;

//===== J1939 MESSAGE =====
struct J1939Message{

  int pgn;
  int spn;
  int value;
};

//===== MESSAGE HISTORY =====
J1939Message history[maxRecords];
int msgIndex = 0;

//===== STORE MESSAGE =====
void storeMessage(J1939Message msg){

  if(msgIndex < maxRecords){

    history[msgIndex] = msg;
    msgIndex++;

    totalMessages++; // count when received
  }
}

//===== DECODE MESSAGE =====
void decodeJ1939(J1939Message msg){


  // ENGINE RPM
  if(msg.pgn == 61444 && msg.spn == 190){

    Serial.print("ENGINE RPM: ");
    Serial.println(msg.value);
  }

  // ENGINE COOLANT TEMP
  else if(msg.pgn == 65262 && msg.spn == 110){

    Serial.print("ENGINE COOLANT TEMP: ");
    Serial.print(msg.value);
    Serial.println(" C");

    if(msg.value > 100){

      Serial.println("ENGINE OVERHEAT WARNING");
    }
  }

  // VEHICLE SPEED
  else if(msg.pgn == 65265 && msg.spn == 84){

    Serial.print("VEHICLE SPEED: ");
    Serial.print(msg.value);
    Serial.println(" KM/H");
  }

  // FUEL LEVEL
  else if(msg.pgn == 65276 && msg.spn == 96){

    Serial.print("FUEL LEVEL: ");
    Serial.print(msg.value);
    Serial.println("%");

    if(msg.value < 20){

      Serial.println("LOW FUEL WARNING");
    }
  }

  // BRAKE PRESSURE
  else if(msg.pgn == 65271 && msg.spn == 521){

    Serial.print("BRAKE PRESSURE: ");
    Serial.print(msg.value);
    Serial.println(" PSI");

    if(msg.value < 50){

      Serial.println("BRAKE WARNING");
    }
  }

  // TRANSMISSION GEAR
  else if(msg.pgn == 65269 && msg.spn == 524){

    Serial.print("CURRENT GEAR: ");
    Serial.println(msg.value);

    if(msg.value > 10){

      Serial.println("TRANSMISSION WARNING");
    }
  }

  Serial.print("TOTAL J1939 MESSAGES: ");
  Serial.println(totalMessages);

  if(totalMessages > 15){

    Serial.println("J1939 GATEWAY ENTERING PROTECTION MODE");
  }
  else if(totalMessages > 10){

    Serial.println("J1939 NETWORK TRAFFIC HIGH");
  }

  Serial.println();
}

//===== SHOW MESSAGE HISTORY =====
void showHistory(){

  Serial.println("\n===== J1939 HISTORY =====");

  for(int i = 0; i < msgIndex; i++){

    decodeJ1939(history[i]);
  }

  Serial.print("TOTAL J1939 MESSAGES");

  Serial.println(totalMessages);
}

//===== SHOW ONLY WARNINGS =====
void showWarnings(){

  Serial.println("\n===== WARNING MESSAGES =====");

  for(int i = 0; i < msgIndex; i++){

    if(history[i].pgn == 65262 &&
       history[i].spn == 110 &&
       history[i].value > 100){

      Serial.println("ENGINE OVERHEAT WARNING");
    }

    if(history[i].pgn == 65276 &&
       history[i].spn == 96 &&
       history[i].value < 20){

      Serial.println("LOW FUEL WARNING");
    }

    if(history[i].pgn == 65271 &&
       history[i].spn == 521 &&
       history[i].value < 50){

      Serial.println("BRAKE WARNING");
    }

    if(history[i].pgn == 65269 &&
       history[i].spn == 524 &&
       history[i].value > 10){

      Serial.println("TRANSMISSION WARNING");
    }
  }
}

//===== SETUP =====
void setup(){

  Serial.begin(9600);

  J1939Message engineRPM = {61444,190,1500};
  J1939Message coolant  = {65262,110,110};
  J1939Message speed    = {65265,84,90};
  J1939Message fuel     = {65276,96,15};
  J1939Message brake    = {65271,521,40};
  J1939Message trans    = {65269,524,12};

  // Store messages
  storeMessage(engineRPM);
  storeMessage(coolant);
  storeMessage(speed);
  storeMessage(fuel);
  storeMessage(brake);
  storeMessage(trans);


  // extra messages to exceed 15
  for(int i = 0; i < 10; i++){

    storeMessage(engineRPM);
  }

  // Display history
  showHistory();

  // Display only warnings
  showWarnings();
}

//===== LOOP =====
void loop(){

}
