#include <Arduino.h>

//===== MESSAGE COUNTERS =====
int totalEngineMessages = 0;
int totalBrakeMessages = 0;
int totalTransMessages = 0;

//===== J1939 MESSAGE =====
struct J1939Message{

  int pgn;
  int spn;
  int value;
  int sourceAddress;
  int destinationAddress;
};

//===== DECODE MESSAGE =====
void decodeJ1939(J1939Message msg){

  Serial.print("MESSAGE FROM ECU ");
  Serial.print(msg.sourceAddress);

  Serial.print(" TO ECU ");
  Serial.println(msg.destinationAddress);

  //===== ENGINE RPM =====
  if(msg.pgn == 61444 &&
     msg.spn == 190){

    Serial.print("ENGINE RPM: ");
    Serial.println(msg.value);

    totalEngineMessages++;
  }

  //===== ENGINE COOLANT TEMP =====
  else if(msg.pgn == 65262 &&
          msg.spn == 110){

    Serial.print("ENGINE TEMP: ");
    Serial.print(msg.value);
    Serial.println(" C");

    totalEngineMessages++;
  }

  //===== BRAKE PRESSURE =====
  else if(msg.pgn == 65271 &&
          msg.spn == 521){

    Serial.print("BRAKE PRESSURE: ");
    Serial.print(msg.value);
    Serial.println(" PSI");

    totalBrakeMessages++;
  }

  //===== TRANSMISSION =====
  else if(msg.pgn == 65269 &&
          msg.spn == 524){

    Serial.print("CURRENT GEAR: ");
    Serial.println(msg.value);

    totalTransMessages++;
  }

  Serial.println();
}

//===== SHOW NETWORK MONITOR =====
void showNetworkMonitor(){

  Serial.println("===== NETWORK MONITOR =====");

  Serial.print("ENGINE MESSAGES: ");
  Serial.println(totalEngineMessages);

  Serial.print("BRAKE MESSAGES: ");
  Serial.println(totalBrakeMessages);

  Serial.print("TRANS MESSAGES: ");
  Serial.println(totalTransMessages);

  if(totalEngineMessages > 10){

    Serial.println("EXCESSIVE ECU TRAFFIC DETECTED");
  }

  if(totalBrakeMessages > 10){

    Serial.println("EXCESSIVE ECU TRAFFIC DETECTED");
  }

  if(totalTransMessages > 10){

    Serial.println("EXCESSIVE ECU TRAFFIC DETECTED");
  }
}

//===== SETUP =====
void setup(){

  Serial.begin(9600);

  //===== ENGINE RPM =====
  J1939Message engineRPM;

  engineRPM.pgn = 61444;
  engineRPM.spn = 190;
  engineRPM.value = 1500;
  engineRPM.sourceAddress = 0;
  engineRPM.destinationAddress = 255;

  //===== ENGINE TEMP =====
  J1939Message engineTemp;

  engineTemp.pgn = 65262;
  engineTemp.spn = 110;
  engineTemp.value = 95;
  engineTemp.sourceAddress = 0;
  engineTemp.destinationAddress = 255;

  //===== BRAKE =====
  J1939Message brake;

  brake.pgn = 65271;
  brake.spn = 521;
  brake.value = 120;
  brake.sourceAddress = 11;
  brake.destinationAddress = 255;

  //===== TRANS =====
  J1939Message trans;

  trans.pgn = 65269;
  trans.spn = 524;
  trans.value = 4;
  trans.sourceAddress = 3;
  trans.destinationAddress = 255;

  //===== SIMULATE TRAFFIC =====

  for(int i = 0; i < 10; i++){

    decodeJ1939(engineRPM);
  }

  for(int i = 0; i < 10; i++){

    decodeJ1939(engineTemp);
  }

  for(int i = 0; i < 5; i++){

    decodeJ1939(brake);
  }

  for(int i = 0; i < 5; i++){

    decodeJ1939(trans);
  }

  //===== DISPLAY SUMMARY =====
  showNetworkMonitor();
}

//===== LOOP =====
void loop(){

}
