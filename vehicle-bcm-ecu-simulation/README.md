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

##  EEPROM Service Counter System
Simulates an ECU maintenance/service counter using EEPROM memory with serial command control.

*Commands:*
- C → Increase service count
- R → Reset service count

*Concepts:* EEPROM storage, serial communication, service interval tracking

## System Description

### Features
- EEPROM memory storage
- Service counter reset
- Serial diagnostic command interface

---

## Temperature Storage & Warning System
Simulates ECU temperature storage using EEPROM with overheating warning detection.

*Commands:*
- S → Save temperature
- R → Read stored temperature

*Features:*
- EEPROM temperature storage
- Overheat warning detection
- Serial diagnostic interface

*Concepts:* EEPROM memory, fault monitoring, embedded diagnostics

---

## Smart Truck Data Logger
Simulates a truck ECU data logging system using EEPROM memory for storing temperature and pressure records.

*Commands:*
- S → Save sensor record
- R → Read stored records
- C → Clear memory

*Features:*
- Multi-record EEPROM storage
- Temperature & pressure monitoring
- Overheat and low-pressure warnings
- Diagnostic serial interface

---

##  Smart Truck RPM Logger
Simulates RPM data storage and retrieval using EEPROM memory.

*Commands:*
- S → Save RPM record
- R → Read RPM records

*Features:*
- EEPROM RPM storage
- Multi-record logging
- Serial diagnostic interface



*Concepts:* Embedded data logging, EEPROM memory, fault monitoring, vehicle diagnostics

---

##  Smart Truck Black Box ECU System
Simulates a vehicle event data recorder (black box) that stores temperature, pressure, and speed data using EEPROM memory.

*Commands:*
- S → Save sensor snapshot
- R → Read stored records
- C → Clear memory

*Features:*
- Multi-parameter data logging
- EEPROM record storage
- Fault condition detection
- Serial diagnostic interface

*Warnings:*
- Overheat detection
- Low pressure alert
- Overspeed warning

*Concepts:* Embedded data logging, vehicle black box systems, EEPROM memory, ECU diagnostics

---

## Truck Trip Counter System
Simulates a vehicle ECU trip counter using EEPROM memory to store and retrieve trip counts.

*Commands:*
- S → Store trip count
- R → Read saved trips

*Features:*
- Persistent trip storage (EEPROM)
- Incremental trip tracking
- Serial-based diagnostic interface


---

## Smart Truck Trip Counter with Reset
Simulates a vehicle ECU trip counter system with EEPROM memory and reset functionality.

*Commands:*
- S → Increment trip count
- R → Read saved trips
- C → Reset trip counter

*Features:*
- Persistent trip storage (EEPROM)
- Reset functionality
- Serial diagnostic control

*Concepts:* Embedded counters, EEPROM memory, vehicle usage tracking

---

## Smart Truck Trip Memory System
Simulates a truck ECU trip memory system using EEPROM to store trip count, distance, and fuel usage records.

*Commands:*
- S → Save trip record
- R → Read stored records
- C → Clear memory

*Features:*
- Multi-record EEPROM storage
- Distance and fuel tracking
- Service warning logic
- Persistent trip memory

*Concepts:* Embedded memory systems, vehicle trip logging, fleet monitoring, ECU diagnostics
