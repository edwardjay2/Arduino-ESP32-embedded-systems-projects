# Vehicle BCM ECU Simulation

## Project Overview
This project simulates a simplified automotive Body Control Module (BCM) / central ECU system using Arduino.

The system monitors multiple vehicle fault inputs and activates a master warning indicator whenever a fault condition is detected.

---

## System Architecture

### Inputs
- Coolant warning switch
- Brake switch
- Door switch
- Pressure warning switch

### Processing
- Centralized ECU fault evaluation logic

### Output
- Master warning LED / buzzer

---

## Working Principle

If ANY fault condition becomes active:
- Coolant fault
- Brake fault
- Door fault
- Pressure fault

The ECU activates the master warning system.

---

## ECU Logic

```text
ANY fault detected → Warning ON
No faults detected → Warning OFF

---

## EEPROM Service Reset System

### Overview
This module simulates an ECU service reset system using EEPROM memory storage.

The system stores service-related data in non-volatile memory and allows reset operations through serial commands.

---

## System Description

### Features
- EEPROM memory storage
- Service counter reset
- Serial diagnostic command interface

### Command
```text
R → Reset service count
