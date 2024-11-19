#include <Arduino.h>

#include <Wire.h>

#include <esp_now.h>
#include <WiFi.h>

#include "classes/light/LightSensor.h"
#include "classes/CO2/CO2Sensor.h"
#include "classes/tempHumidity/TempHumiditySensor.h"


//Access Point
#define BUTTON_PIN 13
const char* masterSSID = "Environmental Node HUB";
const char* password = "staging_password_123";
bool isConnectedToMaster = false;
String masterMacAddress;

LightSensor lightSensor;
CO2Sensor co2Sensor;
TempHumiditySensor tempHumiditySensor;

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
    Wire.begin();

    scani2c();

    lightSensor.begin();
    co2Sensor.begin();
    tempHumiditySensor.begin();



  //ESP-NOW
  // pinMode(BUTTON_PIN, INPUT_PULLUP);
  // WiFi.mode(WIFI_STA);

}
void loop() {
    delay(2500);
    lightSensor.readLight();
    
    delay(2500);
    tempHumiditySensor.readTemp();

    delay(2500);
    tempHumiditySensor.readHumidity();

    delay(2500);
    co2Sensor.readCO2();

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


}