uint8_t byte0 = 0xDC;
uint8_t byte1 = 0X05;

// Little Endian
int rpmLittle = (byte1 << 8) | byte0;

// Big Endian
int rpmBig = (byte0 << 8) | byte1;

Serial.print("Little Endian RPM: ");
Serial.println(rpmLittle);

Serial.print("Big Endian RPM: ");
Serial.println(rpmBig);

