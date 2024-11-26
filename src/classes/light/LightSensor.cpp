#include "LightSensor.h"
#include <BH1750.h>

BH1750 lightMeter;

LightSensor::LightSensor(){
    interval = 5000;
    last_measurement = 0;
}

void LightSensor::begin() {
    lightMeter.begin();
    last_measurement = millis();
}

bool LightSensor::readLight() {
    //Verify interval
    unsigned int currentTime = millis();
    unsigned int elapsed = currentTime - last_measurement;
    
    if (elapsed < interval) { return state; }
    
    last_measurement = currentTime;

    //Measure
    float lux = lightMeter.readLightLevel();
    if (lux >= 0) {
        Serial.print("Light Level: ");
        Serial.print(lux);
        Serial.println(" lx");
        state = true;
    }
    else{
        state = false;
    }

    return state;
}
