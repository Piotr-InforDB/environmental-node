#include "LightSensor.h"
#include <BH1750.h>

BH1750 lightMeter;

LightSensor::LightSensor(){
    interval = 45000;
    last_measurement = 99999;
    state = -9999;
}

void LightSensor::begin() {
    lightMeter.begin();
}

float LightSensor::readLight() {
    //Verify interval
    unsigned int currentTime = millis();
    unsigned int elapsed = currentTime - last_measurement;
    
    if (elapsed < interval) { return 9999; }
    
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
        state = -9999;
    }

    return state;
}
