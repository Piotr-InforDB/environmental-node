#include "LightSensor.h"
#include <BH1750.h>

BH1750 lightMeter;

LightSensor::LightSensor(){
    interval = 5000;
    last_measurement = 0;
    state = -1;
}

void LightSensor::begin() {
    lightMeter.begin();
    last_measurement = millis();
}

float LightSensor::readLight() {
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
        state = lux;
    }
    else{
        state = -1;
    }

    return state;
}
