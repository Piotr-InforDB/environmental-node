#include <Arduino.h>

#include <DHT.h>
#include <Wire.h>

#include "SensirionI2CScd4x.h"
#include <esp_now.h>
#include <WiFi.h>

#include "classes/light/LightSensor.h"


// Temp & Humidity
#define DHTPIN 23
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// CO2
SensirionI2CScd4x scd4x;

//Access Point
#define BUTTON_PIN 13
const char* masterSSID = "Environmental Node HUB";
const char* password = "staging_password_123";
bool isConnectedToMaster = false;
String masterMacAddress;

LightSensor lightSensor;


void runCO2(){
    uint16_t co2;
    float temperature;
    float humidity;
    uint16_t error;

    error = scd4x.readMeasurement(co2, temperature, humidity); // Read CO2 and ignore temp/humidity
    if (error) {
        Serial.println(error);
    } else {
        Serial.print("CO2: ");
        Serial.print(co2);
        Serial.println(" ppm");

        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println("°C");

    }
}
void runTempHumidity(){
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%");

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");
}

void connectToMaster() {
  Serial.println("Button pressed. Scanning for Master...");

  int networksFound = WiFi.scanNetworks();

  for (int i = 0; i < networksFound; i++) {
    if (WiFi.SSID(i) == masterSSID) {
      Serial.println("Master AP found. Connecting...");

      WiFi.begin(masterSSID, password);

      int attempt = 0;
      while (WiFi.status() != WL_CONNECTED && attempt < 10) {
        delay(500);
        attempt++;
      }

      if (WiFi.status() == WL_CONNECTED) {
        isConnectedToMaster = true;
        masterMacAddress = WiFi.BSSIDstr(i);

        Serial.println("\nConnected to Master AP");
        Serial.print("Master MAC Address: ");
        Serial.println(masterMacAddress);
      } else {
        Serial.println("\nFailed to connect to Master AP");
      }
      break;
    }
  }

  // If no master AP found
  if (masterMacAddress == "") {
    Serial.println("Master AP not found. Retry when button is pressed again.");
  }
}

void scani2c(){
    Serial.println("Scanning...");
    byte count = 0;
    for (byte i = 8; i < 120; i++) {
        Wire.beginTransmission(i);
        if (Wire.endTransmission() == 0) {
            Serial.print("Found I2C Device at: 0x");
            Serial.println(i, HEX);
            count++;
        }
    }
    Serial.print("Found ");
    Serial.print(count);
    Serial.println(" device(s).");
}

void setup() {
    Serial.begin(115200);
    Wire.begin(21, 22);
    lightSensor.begin();
    scani2c();

    // scd4x.begin(Wire);

    
    // dht.begin();

    // Start periodic measurement
    // uint16_t error = scd4x.startPeriodicMeasurement();
    // if (error) {
    //     Serial.print("INIT ERROR");
    //     Serial.println(error);
    // } else {
    //     Serial.println("Started periodic measurement.");
    // }

  //ESP-NOW
  // pinMode(BUTTON_PIN, INPUT_PULLUP);
  // WiFi.mode(WIFI_STA);

}
void loop() {

    // lightSensor.readLight();

    // runCO2();
    // runTempHumidity();
    // runLight();

  // if (digitalRead(BUTTON_PIN) == LOW) {
  //   if (!isConnectedToMaster) {
  //     connectToMaster();
  //   }
  // } else {
  //   // If button is released, disconnect from master AP
  //   if (isConnectedToMaster) {
  //     WiFi.disconnect(true);
  //     Serial.println("Disconnected from Master AP");
  //     isConnectedToMaster = false;
  //     masterMacAddress = ""; // Clear stored MAC address
  //   }
  // }

  delay(2500); // Short delay to debounce button

}