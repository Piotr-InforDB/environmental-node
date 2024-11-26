#include "CommunicationController.h"
#include <WiFi.h>
#include <Arduino.h>

#define BUTTON_PIN 12

CommunicationController::CommunicationController(){
    state = "IDLE";
    mac_address = "";
}

void CommunicationController::begin(){
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    WiFi.mode(WIFI_STA);
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
        Serial.println("\nConnected to Master AP");
        Serial.print("Master MAC Address: ");
        Serial.println(mac_address);
      }
      else {
        state = "IDLE";
        Serial.println("\nFailed to connect to Master AP");
      }
      break;
    }
  }

    if(mac_address == ""){
      state = "IDLE";
    }
}