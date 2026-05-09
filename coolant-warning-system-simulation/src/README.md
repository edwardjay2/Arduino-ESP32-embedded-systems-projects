# Coolant Warning System Simulation (Embedded ECU Concept)

## Project Overview
This project simulates a basic automotive ECU input/output system using Arduino. It monitors a coolant switch (simulated sensor) and activates a warning LED when a low coolant condition is detected.

## System Description
- Input: Coolant level switch (digital signal)
- Processing: ECU logic (Arduino)
- Output: Warning LED indicator

## Working Principle
- When coolant switch is CLOSED (LOW signal), it indicates low coolant level
- The system activates a warning LED
- When switch is OPEN (HIGH signal), system returns to normal state

## Logic
- LOW signal → Warning ON
- HIGH signal → Warning OFF

## Code Summary
The Arduino reads a digital input pin and controls an output pin based on the sensor state.

## Hardware Used
- Arduino Uno
- Switch (simulated coolant sensor)
- LED (warning indicator)
- Resistor (for LED protection)

## Learning Outcome
- Digital input/output handling
- ECU-style decision logic
- Basic automotive embedded system simulation

## Future Improvement
- Add buzzer alarm
- Store fault state in EEPROM
- Expand to multi-sensor ECU system
