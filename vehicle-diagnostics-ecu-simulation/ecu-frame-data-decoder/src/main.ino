if(frame.data[0] == 0){
  
  Serial.println("ENGINE DATA");

  Serial.print("ENGINE TEMP: ");
  Serial.println(frame.data[1]);

  Serial.print("ENGINE RPM: ");
  Serial.println(frame.data[2]);

  if(frame.data[1] > 100){

    Serial.println("ENGINE OVERHEAT WARNING");
  }
}

if(frame.data[0] == 1){

  Serial.println("TRANSMISSION DATA");

  Serial.print("CURRENT GEAR: ");
  Serial.println(frame.data[1]);

  Serial.print("TRANSMISSION OIL TEMP: ");
  Serial.println(frame.data[2]);

  if(frame.data[2] > 100){

    Serial.println("TRANSMISSION OVERHEAT WARNING");
  }
}

if(frame.data[0] == 1){

  Serial.println("BRAKE DATA");

  Serial.print("BRAKE PRESSURE: ");
  Serial.println(frame.data[1]);

  Serial.print("ABS STATUS: ");
  Serial.println(frame.data[2]);

  if(frame.data[2] == 1){

    Serial.println("ABS STATUS: ACTIVE");
  }
  else{

    Serial.println("ABS STATUS: INACTIVE");
  }
}

if(frame.data[0] == 2){

  Serial.println("BODY CONTROL");

  Serial.print("DOOR STATUS: ");
  Serial.println(frame.data[1]);

  if(frame.data[1] == 1){ // IF DOOR STATUS IS ACTVATED

    Serial.println("DOOR: OPEN"); // 1- BOOLEAN TRUE - OPEN

  }
  else{

    Serial.println("DOOR: CLOSED"); //0- BOOLEAN FALSE - CLOSE
  }

  Serial.print("SEATBELT STATUS: ");
  Serial.println(frame.data[2]);

  if(frame.data[2] == 1){

    Serial.println("SEATBELT: FASTENED");
  }
  else{

    Serial.println("SEATBELT: NOT FASTENED");
  }
}
