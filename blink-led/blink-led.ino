void setup() {
    pinMode(2, OUTPUT); // Set built-in LED pin as output
}

void loop() {
    digitalWrite(2, HIGH); // Turn LED on
    delay(1000);            // Wait 1 second
    digitalWrite(2, LOW);   // Turn LED off
    delay(1000);            // Wait 1 second
}
