#include "CO2Sensor.h"
#include <Wire.h>

SensirionI2CScd4x scd4x;

CO2Sensor::CO2Sensor(){
    interval = 5000;
    last_measurement = 0;
    state = -1;
}

void CO2Sensor::begin(){
    scd4x.begin(Wire);
    scd4x.startPeriodicMeasurement();
    last_measurement = millis();
}
float CO2Sensor::readCO2(){
    //Verify interval
    unsigned int currentTime = millis();
    unsigned int elapsed = currentTime - last_measurement;
    
    if (elapsed < interval) { return state; }
    
    last_measurement = currentTime;

    //Measure
    uint16_t error;
    char errorMessage[256];

    uint16_t co2;
    float temperature;
    float humidity;
    
    error = scd4x.readMeasurement(co2, temperature, humidity);
    if (error || !co2) {
        state = false;
    }
    else {
        Serial.print("Co2:");
        Serial.println(co2);
    
        state = static_cast<float>(co2);
    }

    return state;
}



