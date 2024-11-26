#include <Arduino.h>

#include <Wire.h>

#include "classes/light/LightSensor.h"
#include "classes/CO2/CO2Sensor.h"
#include "classes/tempHumidity/TempHumiditySensor.h"
#include "classes/leds/LedsController.h"
#include "classes/communication/CommunicationController.h"

//Access Point

LightSensor lightSensor;
CO2Sensor co2Sensor;
TempHumiditySensor tempHumiditySensor;
LedsController ledsController;
CommunicationController communicationController;

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

    // scani2c();

    lightSensor.begin();
    delay(500);

    tempHumiditySensor.begin();
    delay(500);

    co2Sensor.begin();
    delay(500);

    communicationController.begin();
    delay(500);

}
void loop() {
    ledsController.setLight( lightSensor.readLight() );
    ledsController.setTemp( tempHumiditySensor.readTemp() );
    ledsController.setHumidity( tempHumiditySensor.readHumidity() );
    ledsController.setCO2( co2Sensor.readCO2() );
    ledsController.setConnection( communicationController.run() );
    delay(500);

}