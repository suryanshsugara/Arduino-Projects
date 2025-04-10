# Voice-Controlled Curtain System Using ESP32/ESP8266 and Sinric Pro

## Overview
This project demonstrates how to build a voice-controlled curtain system using an ESP32 or ESP8266 microcontroller, an L293D motor driver, and Sinric Pro for voice control integration. The system allows you to open and close curtains via Alexa or Google Assistant commands. The motor automatically stops after 25 seconds, and the switch state in Sinric Pro resets to prevent conflicts between commands.

## Features
- Open curtains with the "Curtain Open" command.
- Close curtains with the "Curtain Close" command.
- Automatic motor stop after 25 seconds to prevent overuse.
- Switch state reset after timeout to ensure proper direction control for subsequent commands.
- Compatible with both ESP32 and ESP8266 boards.
- Integration with Sinric Pro for seamless voice control via Alexa or Google Assistant.

## Hardware Requirements
1. **Microcontroller**: ESP32 or ESP8266
2. **Motor Driver**: L293D
3. **DC Motor**: For curtain movement
4. **Power Supply**: Appropriate power source for the motor and microcontroller
5. **Curtain Mechanism**: Pulley system or similar setup for motorized curtain movement
6. Jumper wires, breadboard, and other basic components

## Software Requirements
1. Arduino IDE (with ESP32/ESP8266 board support installed)
2. Sinric Pro library:
   - Install via Arduino Library Manager (`Tools > Manage Libraries > Search for "Sinric Pro"`).
3. Dependencies:
   - `ArduinoJson` library (required by Sinric Pro)
   - `WiFi` library (comes pre-installed with ESP32/ESP8266 board support)

## Circuit Diagram
### L293D Motor Driver Pin Configuration
| Pin Name       | Connection                          |
|----------------|-------------------------------------|
| Enable Pin     | GPIO 14 (ESP32/ESP8266)            |
| Input 1        | GPIO 26 (ESP32/ESP8266)            |
| Input 2        | GPIO 27 (ESP32/ESP8266)            |
| Motor Outputs  | Connect to DC motor terminals      |
| VCC            | Power supply for L293D (e.g., 5V)  |
| GND            | Common ground                      |

### Microcontroller Connections
- Connect the Enable Pin, Input 1, and Input 2 of the L293D to the respective GPIO pins on your microcontroller.
- Connect the motor terminals to the output pins of the L293D.

## Sinric Pro Setup

### Step 1: Create Devices
1. Log in to [Sinric Pro](https://sinric.pro).
2. Add two devices:
   - Device 1: "Curtain Open" (Switch type)
   - Device 2: "Curtain Close" (Switch type)
3. Note down the unique Device IDs for both devices.

### Step 2: Link Alexa or Google Assistant
1. Link your Sinric Pro account with Alexa or Google Assistant.
2. Use voice commands like "Turn on Curtain Open" or "Turn on Curtain Close."

## How It Works
1. When you activate "Curtain Open," the motor rotates forward for up to **25 seconds**, then stops automatically.
2. When you activate "Curtain Close," the motor rotates backward for up to **25 seconds**, then stops automatically.
3. After stopping automatically or manually turning off a command, the switch state in Sinric Pro resets to prevent conflicts.

## License
This project is released under the [MIT License](https://opensource.org/licenses/MIT).

Feel free to contribute by submitting issues or pull requests!
