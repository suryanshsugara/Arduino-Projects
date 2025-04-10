#define ENABLE_DEBUG

#include <Arduino.h>
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
#elif defined(ESP32) || defined(ARDUINO_ARCH_RP2040)
  #include <WiFi.h>
#endif

#include "SinricPro.h"
#include "SinricProSwitch.h"

// WiFi Credentials and Sinric Pro App details
#define WIFI_SSID         "Your_WiFi_SSID"
#define WIFI_PASS         "Your_WiFi_Password"
#define APP_KEY           "Your_App_Key"
#define APP_SECRET        "Your_App_Secret"

// SinricPro Device IDs
#define SWITCH_ID_OPEN    "Device_ID_For_Curtain_Open"
#define SWITCH_ID_CLOSE   "Device_ID_For_Curtain_Close"

// L293D Motor Driver Pin Definitions
#define ENABLE_PIN        14    // Enable pin
#define MOTOR_IN1         26    // Input pin 1
#define MOTOR_IN2         27    // Input pin 2

// Global variables for motor runtime management
bool motorActive = false;
unsigned long motorStartTime = 0;
String activeDeviceId = ""; // Tracks active device ID

// Function to stop the motor and reset switch state
void stopMotorAndResetSwitch() {
  Serial.println("Stopping motor...");
  
  digitalWrite(ENABLE_PIN, LOW); // Disable motor
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  
  if (activeDeviceId != "") {
    Serial.printf("Resetting switch state for device: %s\n", activeDeviceId.c_str());
    SinricProSwitch& activeSwitch = SinricPro[activeDeviceId];
    activeSwitch.sendPowerStateEvent(false); // Turn off switch in Sinric Pro
    activeDeviceId = ""; // Clear active device ID
  }
  
  motorActive = false;
}

// Callback for opening curtains
bool onPowerStateOpen(const String &deviceId, bool &state) {
  if (state) {
    Serial.println("Opening curtains...");
    digitalWrite(MOTOR_IN1, HIGH);
    digitalWrite(MOTOR_IN2, LOW);
    digitalWrite(ENABLE_PIN, HIGH);
    
    motorActive = true;
    motorStartTime = millis();
    activeDeviceId = SWITCH_ID_OPEN;
  } else {
    stopMotorAndResetSwitch();
  }
  
  return true;
}

// Callback for closing curtains
bool onPowerStateClose(const String &deviceId, bool &state) {
  if (state) {
    Serial.println("Closing curtains...");
    digitalWrite(MOTOR_IN1, LOW);
    digitalWrite(MOTOR_IN2, HIGH);
    digitalWrite(ENABLE_PIN, HIGH);
    
    motorActive = true;
    motorStartTime = millis();
    activeDeviceId = SWITCH_ID_CLOSE;
  } else {
    stopMotorAndResetSwitch();
  }
  
  return true;
}

void setupWiFi() {
  Serial.printf("\r\n[WiFi]: Connecting");
  
#if defined(ESP8266)
    WiFi.setSleepMode(WIFI_NONE_SLEEP);
#elif defined(ESP32)
    WiFi.setSleep(false);
#endif
  
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
  }
  
  Serial.printf("\n[WiFi]: Connected! IP Address: %s\n", WiFi.localIP().toString().c_str());
}

void setupSinricPro() {
  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);

  stopMotorAndResetSwitch();

  SinricProSwitch& curtainOpen = SinricPro[SWITCH_ID_OPEN];
  curtainOpen.onPowerState(onPowerStateOpen);

  SinricProSwitch& curtainClose = SinricPro[SWITCH_ID_CLOSE];
  curtainClose.onPowerState(onPowerStateClose);

  SinricPro.onConnected([](){ Serial.println("Connected to Sinric Pro!"); });
  
  SinricPro.begin(APP_KEY, APP_SECRET);
}

void setup() {
  Serial.begin(115200);
  
  setupWiFi();
  
  setupSinricPro();
}

void loop() {
  SinricPro.handle();

  if (motorActive && millis() - motorStartTime >= 25000) {
    Serial.println("25 seconds elapsed. Stopping motor.");
    stopMotorAndResetSwitch();
  }
}
