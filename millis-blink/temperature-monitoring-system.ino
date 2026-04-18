#include <Arduino.h>

float temperature = 20.0; // starting temp

unsigned long previousTime = 0;
unsigned long interval = 1000; // 1 second

void setup() {
  Serial.begin(9600);
  Serial.println("Temperature Monitoring Sysytem Started");
}
void loop() {
  unsigned long currentMillis = millis();
  // simulate temperature change every 1 second
  if(currentMillis - previousTime >= interval) {
    previousTime = currentMillis;

    // Increase temperature gradually 
    temperature += 2.5;

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" degree celcius");

    //Decision making
    if(temperature < 25) {
      Serial.println("Status: COOL");
    }
    else if  (temperature >= 25 && temperature <= 35) {
      Serial.println("Status: NORMAL");
    } 
    else if (temperature > 35) {
      Serial.println("Status: HOT! Turn on fan");
    }
    }
  

  }
