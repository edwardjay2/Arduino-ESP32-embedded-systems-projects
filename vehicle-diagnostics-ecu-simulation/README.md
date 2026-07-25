# Vehicle Diagnostics ECU Simulation

## Overview
This folder contains Arduino-based projects that simulate vehicle ECU diagnostic systems. The projects demonstrate fault detection, decoding, monitoring, and diagnostic message handling.

---

## Basic Fault Reader

### Overview
Simulates reading basic ECU fault codes from sensors or inputs.

Features:
- Fault detection
- Serial output display
- Simple ECU logic

---

## ECU Fault Decoder

### Overview
Simulates decoding ECU fault codes into readable messages.

Features:
- Fault code interpretation
- Diagnostic message output
- ECU communication logic

---

## Live Diagnostics Monitor

### Overview
Simulates real-time ECU monitoring of vehicle faults.

Features:
- Live fault detection
- Continuous monitoring
- Serial diagnostics display

---

## Advanced Diagnostic Gateway

### Overview
Simulates a central ECU diagnostic gateway that processes multiple fault sources.

Features:
- Multi-ECU diagnostics
- Fault aggregation
- Centralized diagnostic control
- Advanced ECU simulation

---


J1939 Blackbox Recorder

Project Overview

This project simulates a J1939 vehicle blackbox recorder using Arduino and EEPROM.

The system records vehicle messages, detects faults, and stores diagnostic event information.

System Architecture

Inputs

- Engine temperature
- Fuel level
- J1939 PGN/SPN messages

Processing

- J1939 message decoding
- Fault detection
- DTC storage
- Network traffic monitoring
- EEPROM memory storage

Output

- Message history
- Active faults
- Warning events
- Vehicle service warning

Working Principle

The system monitors J1939 messages and records important vehicle events.

If an overheat, low-fuel, or high-network-traffic condition is detected, the system records the event and generates a warning.

Concepts

- J1939 communication
- PGN and SPN
- DTC and FMI
- EEPROM storage
- Blackbox data logging
- Vehicle diagnostics

