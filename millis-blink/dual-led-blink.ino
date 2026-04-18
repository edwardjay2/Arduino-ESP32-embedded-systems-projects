#include <Arduino.h>

// Define LED blink intervals in milliseconds
const unsigned long intervalLED1 = 300; // 0.3 seconds
const unsigned long intervalLED2 = 700; // 0.7 seconds

// variables to track last toggle time
unsigned long previousLED1 = 0; //unsigned long is datatype used to store large positive numbers
unsigned long previousLED2 = 0; 
// int - -32,768 to 32,767 - too small
// long - large (positive & negative)
// unsigned long - 0 to 4 billion

//LED states 
bool led1state = false;
bool led2state = false;

void setup() {
  Serial.begin(9600); // Initialize Serial Monitor
  Serial.println("Non-blocking LED simulation started");
}

void loop() {
  unsigned long currentMillis = millis(); //Current time in ms

  //LED 1 blinking logic
  if (currentMillis - previousLED1 >= intervalLED1) {
    previousLED1 = currentMillis; //Update Last toggle time
    led1state = !led1state;    // Toggle LED state
    Serial.print("LED 1 is");
    Serial.println(led1state ? "ON" : "OFF");
  }

  //LED 2 blinking logic
  if(currentMillis - previousLED2 >= intervalLED2) {
    previousLED2 = currentMillis; //Update Last toggle time
    led2state = !led2state;     // Toggle LED state
    Serial.print("LED 2 is");
    Serial.println(led2state ? "ON" : "OFF");
  }
}
