// New Blynk Template Details
#define BLYNK_TEMPLATE_ID "TMPL3jEzwBxFt"
#define BLYNK_TEMPLATE_NAME "DHT Automation"
#define BLYNK_AUTH_TOKEN "QulOIEc27YBxGl5Z6uyLFYEi_gySBky6"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// WiFi Credentials
char ssid[] = "YOUR WIFI NAME";
char pass[] = "YOUR WIFI PASSWORD";

// Pin Definitions
#define DHTPIN 25       // DHT sensor connected to GPIO 25
#define LEDPIN 14       // LED connected to GPIO 14
#define DHTTYPE DHT11   // DHT11 sensor type

// Initialize DHT sensor and Timer
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// Variable to store LED state
int ledState = LOW;

// Function to read sensor data and send to Blynk
void sendSensor()
{
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Send data to Blynk virtual pins
  Blynk.virtualWrite(V1, temperature); // Temperature on V1
  Blynk.virtualWrite(V2, humidity);    // Humidity on V2

  // Print values to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C\t");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
}

// Function called when switch state changes in Blynk App (V3)
BLYNK_WRITE(V3)
{
  ledState = param.asInt();          // Get switch state from app (0 or 1)
  digitalWrite(LEDPIN, ledState);    // Set LED pin accordingly

  Serial.print("LED is now: ");
  Serial.println(ledState ? "ON" : "OFF");
}

void setup()
{
  Serial.begin(9600);

  pinMode(LEDPIN, OUTPUT);           // Set LED pin as output
  digitalWrite(LEDPIN, LOW);         // Initially turn off LED

  dht.begin();                       // Start the DHT sensor

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); // Connect to WiFi & Blynk server

  timer.setInterval(1000L, sendSensor);      // Send sensor data every second
}

void loop()
{
  Blynk.run();
  timer.run();
}
