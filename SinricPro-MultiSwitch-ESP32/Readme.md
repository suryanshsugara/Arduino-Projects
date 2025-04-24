# SinricPro Multi-Switch ESP32 Example

This project demonstrates how to control multiple relay switches using SinricPro and an ESP32 microcontroller. The setup allows you to manage two switches via Alexa, Google Home, or the SinricPro app, making it ideal for home automation scenarios.

## Features

- Control two independent relays (switches) using SinricPro
- Real-time status updates via the SinricPro cloud
- Compatible with Alexa, Google Home, and SinricPro App
- Modular callback handling for each switch

## Hardware Required

- ESP32 development board
- 2-channel relay module
- Jumper wires
- Breadboard (optional)
- 5V power supply

## Wiring

| ESP32 Pin | Relay Module Channel |
|-----------|---------------------|
| 33        | Relay 1             |
| 35        | Relay 2             |

## Software Setup

1. **Install Arduino IDE:**  
   Download from [arduino.cc](https://www.arduino.cc/en/software).

2. **Install Libraries:**  
   - [SinricPro](https://github.com/sinricpro/esp8266-esp32-sdk)  
   - ESP32 board support

3. **Configure Credentials:**  
   In `main.ino`, replace the following with your own details:
