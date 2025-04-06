# WiFi-DHT11-ThingSpeak

This repository contains an Arduino project that connects to a WiFi network, reads temperature and humidity data from a DHT11 sensor, and uploads the data to ThingSpeak.

## Features
- Reads temperature (Celsius and Fahrenheit) and humidity using a DHT11 sensor.
- Connects to WiFi automatically.
- Uploads data to ThingSpeak using its API.

## Requirements
- Arduino IDE
- ESP32 microcontroller
- DHT11 sensor
- ThingSpeak account with a configured channel

## Setup Instructions
1. Clone this repository:
git clone https://github.com/suryanshsugara/WiFi-DHT11-ThingSpeak.git

2. Open `main.ino` in Arduino IDE.

3. Replace the placeholders in `main.ino` with your WiFi credentials, ThingSpeak channel ID, and API key:
#define SECRET_SSID "Your_WiFi_Name"
#define SECRET_PASS "Your_WiFi_Password"
#define SECRET_CH_ID Your_Channel_ID
#define SECRET_WRITE_APIKEY "Your_API_Key"

4. Connect the DHT11 sensor to pin 33 of your ESP32.
5. Upload the code to your ESP32.
6. Monitor the serial output for connection status and sensor readings.

## Usage
Once set up, the ESP32 will automatically connect to WiFi, read data from the DHT11 sensor, and upload it to ThingSpeak every 20 seconds.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
