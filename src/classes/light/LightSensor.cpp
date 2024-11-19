#include "LightSensor.h"
#include <BH1750.h>

BH1750 lightMeter;

LightSensor::LightSensor(){
    interval = 2500;
    last_measurement = 0;
}

void LightSensor::begin() {
    lightMeter.begin();
}

void LightSensor::readLight() {
    //Verify interval
    unsigned int currentTime = millis();
    unsigned int elapsed = currentTime - last_measurement;
    
    if (elapsed < interval) { return; }
    
    last_measurement = currentTime;

    //Measure
    float lux = lightMeter.readLightLevel();
    if (lux >= 0) {
        Serial.print("Light Level: ");
        Serial.print(lux);
        Serial.println(" lx");
    }
    else{
        Serial.println("Handle Light Error");
    }
}
