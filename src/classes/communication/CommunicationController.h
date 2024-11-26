#ifndef COMMUNICATIONCONTROLLER_H
#define COMMUNICATIONCONTROLLER_H

#include <WiFi.h>
#include <Arduino.h>

class CommunicationController {
public:
    CommunicationController();
    void begin();
    String run();
    void connect();
private:
    String mac_address;
    String state;
    const char* SSID = "Environmental Node HUB";
    const char* password = "staging_password_123";
};

#endif