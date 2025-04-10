# Blynk-DHT11-Automation

This repository contains an IoT project that uses an ESP32 microcontroller to monitor temperature and humidity using a DHT11 sensor and control an LED via the Blynk app.

## Features
- Real-time monitoring of temperature and humidity using the DHT11 sensor.
- Integration with Blynk for cloud-based IoT control and visualization.
- LED control via a virtual switch in the Blynk app.
- Serial output for debugging and monitoring.

## Requirements
- ESP32 microcontroller
- DHT11 sensor
- LED
- Jumper wires
- Breadboard (optional)
- USB cable for programming ESP32

## Software Requirements
- Arduino IDE
- Blynk Library (Install via Arduino Library Manager)
- DHT Sensor Library (Install via Arduino Library Manager)

## Setup Instructions

### Hardware Setup
1. Connect the DHT11 sensor:
   - VCC pin → 3V3 pin of ESP32
   - GND pin → GND pin of ESP32
   - Data pin → GPIO25 of ESP32
2. Connect the LED:
   - Positive terminal → GPIO14 of ESP32 (via resistor if needed)
   - Negative terminal → GND pin of ESP32

### Software Setup
1. Install Arduino IDE from [Arduino's official website](https://www.arduino.cc/en/software).

2. Install the required libraries:
   - Open Arduino IDE, go to `Sketch > Include Library > Manage Libraries`.
   - Search for "Blynk" and install it.
   - Search for "DHT" and install it.

3. Configure your WiFi credentials, Blynk template ID, name, and authentication token in `main.ino`:
#define BLYNK_TEMPLATE_ID "Your_Template_ID"
#define BLYNK_TEMPLATE_NAME "Your_Template_Name"
#define BLYNK_AUTH_TOKEN "Your_Auth_Token"

char ssid[] = "Your_WiFi_Name";
char pass[] = "Your_WiFi_Password";

4. Upload the code (`main.ino`) to your ESP32 using Arduino IDE.

### Blynk Configuration
1. Create a new device in the Blynk app using your template ID and authentication token.
2. Add widgets:
- **Gauge** for temperature (Virtual Pin V1).
- **Gauge** for humidity (Virtual Pin V2).
- **Button** for LED control (Virtual Pin V3).

---

## Usage Instructions
1. Power up your ESP32 after uploading the code.
2. Open the Serial Monitor in Arduino IDE (`Ctrl+Shift+M`) to view connection status and sensor readings.
3. Use the Blynk app to monitor temperature and humidity or control the LED.

---

## Troubleshooting
- **WiFi Connection Issues**:
- Ensure your SSID and password are correct.
- Verify that your router supports 2.4 GHz WiFi (ESP32 does not support 5 GHz).
- **Invalid Sensor Readings**:
- Check wiring connections between ESP32 and DHT11 sensor.
- Ensure proper power supply to the sensor.

---

## Applications
- Home Automation: Monitor indoor temperature and humidity levels while controlling devices remotely.
- Weather Stations: Build an IoT-enabled weather monitoring system.
- Smart Agriculture: Track environmental conditions for farming purposes.

---

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
