#include "LightSensor.h"
#include <Arduino.h>
#include <BH1750.h>

BH1750 lightMeter;
unsigned int interval;
unsigned int last_measurement = 0;

LightSensor::LightSensor(){
    interval = 2500;
}

void LightSensor::begin() {

    lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x23);
    // lightMeter.configure(BH1750::CONTINUOUS_HIGH_RES_MODE);

    if (!lightMeter.begin()) {
        Serial.println("Failed to initialize BH1750 light sensor!");
    } else {
        Serial.println("BH1750 light sensor initialized.");
    }
}

void LightSensor::readLight() {
    unsigned int currentTime = millis();
    unsigned int elapsed = currentTime - last_measurement;
    
    if (elapsed < interval) { return; }
    
    last_measurement = currentTime;

    float lux = lightMeter.readLightLevel();
    if (lux >= 0) {
        Serial.print("Light Level: ");
        Serial.print(lux);
        Serial.println(" lx");
    }
}
