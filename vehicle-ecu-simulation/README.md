# Vehicle ECU Simulation

Automotive embedded systems projects focused on ECU logic, coolant warning system, brake light ECU etc using Arduino.

---

## Coolant Warning System
Monitors coolant switch input and activates a warning indicator when low coolant is detected.

*Concepts:* Digital input/output, ECU warning logic

---

## Brake Light ECU
Simulates brake pedal switch logic for brake light activation.

*Concepts:* Embedded control logic, automotive lighting system

---

## Door Warning System
Triggers buzzer/LED warning when vehicle door is open.

*Concepts:* BCM logic, state monitoring

---

## Pressure Alarm System
Uses millis() timing logic to flash warning LED during low pressure condition.

*Concepts:* Non-blocking timers, embedded alarm systems

---

## Fan Control System
Activates cooling fan warning when high temperature or low pressure is detected.

*Concepts:* Multi-input ECU logic, OR conditions

---

## EEPROM Service Reset
Simulates ECU service reset and non-volatile memory storage using EEPROM.

*Concepts:* EEPROM memory, serial commands, ECU diagnostics

---

## Central Fault Monitoring ECU
Monitors multiple vehicle fault inputs and activates a master warning output.

*Inputs:*
- Coolant
- Brake
- Door
- Pressure

*Concepts:* BCM architecture, centralized fault management

---

## Technologies Used
- Arduino C/C++
- Digital I/O
- Embedded Logic
- Serial Communication


