#ifdef ENABLE_DEBUG
   #define DEBUG_ESP_PORT Serial
   #define NODEBUG_WEBSOCKETS
   #define NDEBUG
#endif 

#include <Arduino.h>
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
#elif defined(ESP32) || defined(ARDUINO_ARCH_RP2040)
  #include <WiFi.h>
#endif

#include "SinricPro.h"
#include "SinricProSwitch.h"

#define WIFI_SSID         "Wifi ka bill tera baap bharega"
#define WIFI_PASS         "12345678"
#define APP_KEY           "52fb842f-3f25-4701-939b-8a5bc72ff4ff"
#define APP_SECRET        "b22cf429-0b2b-4e22-8f1f-fb1f5c2e9ce0-5abec933-05ca-46c0-9e5f-62839215e3cf"

#define SWITCH_ID_1       "67da6e6cdc4a25d5c393274f"
#define RELAYPIN_1        33

#define SWITCH_ID_2       "67da70408ed485694cfbd1aa"
#define RELAYPIN_2        35

#define BAUD_RATE         115200

bool onPowerState1(const String &deviceId, bool &state) {
 Serial.printf("Device 1 turned %s\n", state ? "on" : "off");
 digitalWrite(RELAYPIN_1, state ? LOW : HIGH);
 return true;
}

bool onPowerState2(const String &deviceId, bool &state) {
 Serial.printf("Device 2 turned %s\n", state ? "on" : "off");
 digitalWrite(RELAYPIN_2, state ? LOW : HIGH);
 return true;
}

void setupWiFi() {
  Serial.printf("\r\n[Wifi]: Connecting");

  #if defined(ESP8266)
    WiFi.setSleepMode(WIFI_NONE_SLEEP); 
    WiFi.setAutoReconnect(true);
  #elif defined(ESP32)
    WiFi.setSleep(false); 
    WiFi.setAutoReconnect(true);
  #endif

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
  }

  Serial.printf("connected!\r\n[WiFi]: IP-Address is %s\r\n", WiFi.localIP().toString().c_str());
}

void setupSinricPro() {
  pinMode(RELAYPIN_1, OUTPUT);
  pinMode(RELAYPIN_2, OUTPUT);
    
  SinricProSwitch& mySwitch1 = SinricPro[SWITCH_ID_1];
  mySwitch1.onPowerState(onPowerState1);
  
  SinricProSwitch& mySwitch2 = SinricPro[SWITCH_ID_2];
  mySwitch2.onPowerState(onPowerState2);
  
  SinricPro.onConnected([](){ Serial.printf("Connected to SinricPro\r\n"); }); 
  SinricPro.onDisconnected([](){ Serial.printf("Disconnected from SinricPro\r\n"); });
   
  SinricPro.begin(APP_KEY, APP_SECRET);
}

void setup() {
  Serial.begin(BAUD_RATE); Serial.printf("\r\n\r\n");
  setupWiFi();
  setupSinricPro();
}

void loop() {
  SinricPro.handle();
}
