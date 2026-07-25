#include <Arduino.h>

//=== CAN FRAME ===
struct CANFrame{

  uint32_t id;
  uint8_t dlc;
  uint8_t data[8];
};

//== DECODE CAN FRAME ===
void decodeCANFrame(const CANFrame &frame){

  Serial.println("CAN FRAME RECEIVED");
  Serial.println();

  Serial.print("ID: 0x");
  Serial.println(frame.id, HEX);

  Serial.print("DLC: ");
  Serial.println(frame.dlc);

  

  Serial.print("VALID DATA BYTES RECEIVED: ");
  Serial.println(frame.dlc);

  Serial.print("ENGINE TEMP: ");
  Serial.print(frame.data[0]);
  Serial.println(" C");

  if(frame.data[0] > 100){

    Serial.println("ENGINE OVERHEAT WARNING");
  }

  Serial.print("CURRENT GEAR: ");
  Serial.println(frame.data[1]);

  Serial.print("BRAKE PRESSURE: ");
  Serial.print(frame.data[2]);
  Serial.println(" PSI");

  Serial.print("VEHICLE SPD: ");
  Serial.print(frame.data[3]);
  Serial.println(" KM/H");

  Serial.print("FUEL LEVEL: ");
  Serial.print(frame.data[4]);
  Serial.println(" %");

  if(frame.data[4] < 20){

    Serial.println("LOW FUEL WARNING");
  }

  Serial.print("TIRE PRESSURE: ");
  Serial.print(frame.data[5]);
  Serial.println(" PSI");

  if(frame.data[5] < 30){

    Serial.println("LOW TIRE PRESSURE WARNING");
  }

  Serial.print("DOOR STATUS: ");
  Serial.println(frame.data[6]);

  Serial.print("SUSPENSION STATUS: ");
  Serial.println(frame.data[7]);

  
}

//=== SETUP ===
void setup(){

  Serial.begin(9600);

  CANFrame dashboardFrame;

  dashboardFrame.id = 0x401;

  dashboardFrame.dlc = 8;

  dashboardFrame.data[0] = 95;

  dashboardFrame.data[1] = 6;

  dashboardFrame.data[2] = 130;

  dashboardFrame.data[3] = 90;

  dashboardFrame.data[4] = 45;

  dashboardFrame.data[5] = 25;

  dashboardFrame.data[6] = 1;

  dashboardFrame.data[7] = 2;

  decodeCANFrame(dashboardFrame);

}

//=== LOOP ===
void loop(){

}

