#include "CommunicationController.h"
#include <WiFi.h>
#include <Arduino.h>
#include <Preferences.h>
#include <esp_now.h>

#define BUTTON_PIN 12

CommunicationController::CommunicationController(){
    state = "IDLE";
    mac_address = "";
}

void CommunicationController::begin(){
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    WiFi.mode(WIFI_STA);
    preferences.begin("env-node", false);

    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW initialization failed!");
        state = "ERROR";
    }

    mac_address = preferences.getString("mac_address", "");
    if(mac_address != ""){
      state = "CONNECTED";
    }
}
String CommunicationController::run() {

    if(state == "CONNECTING"){
        this->connect();
    }

    if (digitalRead(BUTTON_PIN) == LOW) {
        mac_address = "";
        state = "CONNECTING";
    }

    return state;

}

void CommunicationController::connect() {
  Serial.println("Button pressed. Scanning for Master...");

  int networksFound = WiFi.scanNetworks();

  for (int i = 0; i < networksFound; i++) {
    if (WiFi.SSID(i) == SSID) {
      Serial.println("Master AP found. Connecting...");

      WiFi.begin(SSID, password);

      int attempt = 0;
      while (WiFi.status() != WL_CONNECTED && attempt < 10) {
        delay(500);
        attempt++;
      }

      if (WiFi.status() == WL_CONNECTED) {
        state = "CONNECTED";
        mac_address = WiFi.BSSIDstr(i);
        Serial.print("\nConnected to HUB");
        Serial.println(mac_address);
      }
      else {
        state = "IDLE";
        Serial.println("\nFailed to connect to HUB");
      }
      break;
    }
  }

    if(mac_address == ""){
      state = "IDLE";
    }
    preferences.putString("mac_address", mac_address);
}


void CommunicationController::sendData(String key, float value){
  if(value == -9999 || value == 9999){ return; }

    uint8_t receiverMAC[6];
    if (sscanf(this->mac_address.c_str(), "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
              &receiverMAC[0], &receiverMAC[1], &receiverMAC[2],
              &receiverMAC[3], &receiverMAC[4], &receiverMAC[5]) != 6) {
        Serial.println("Invalid MAC address format");
        return;
    }

    Serial.printf("Peer MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
            receiverMAC[0], receiverMAC[1], receiverMAC[2],
            receiverMAC[3], receiverMAC[4], receiverMAC[5]);


    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, receiverMAC, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    peerInfo.ifidx = WIFI_IF_STA;

    if (!esp_now_is_peer_exist(receiverMAC)) {
        if (esp_now_add_peer(&peerInfo) != ESP_OK) {
            Serial.println("Failed to add peer");
            return;
        }
    }

    String data = "{\"key\":\"" + key + "\", \"value\":\"" + value + "\"}";
    Serial.println(data);

    const char *message = data.c_str();
    size_t messageLen = strlen(message);

    esp_err_t result = esp_now_send(receiverMAC, (uint8_t *)message, messageLen);

    if (result == ESP_OK) {
        Serial.println("Data sent successfully");
    } else {
        Serial.printf("Error sending data: %d\n", result);
    }
}