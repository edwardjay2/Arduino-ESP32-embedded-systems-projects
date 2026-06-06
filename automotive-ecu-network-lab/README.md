Automotive ECU Network Lab

Project Overview

This folder contains Arduino-based projects that simulate communication between multiple automotive Electronic Control Units (ECUs). The projects demonstrate how ECUs exchange fault messages, process diagnostic information, and manage vehicle network communication.

System Architecture

Simulated ECUs

- Engine ECU
- Brake ECU
- Transmission ECU

Processing

- ECU message transmission
- Fault message decoding
- Fault history logging
- Message filtering

Output

- Serial Monitor diagnostic messages
- Fault history display

Working Principle

When an ECU detects a fault, it sends a fault message to the simulated network.

The system then:

- Receives the ECU message
- Stores the fault information
- Decodes the fault code
- Displays the diagnostic message
- Filters and manages fault history
