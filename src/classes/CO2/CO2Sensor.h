#ifndef CO2SENSOR_H
#define CO2SENSOR_H

#include <Wire.h>
#include "SensirionI2CScd4x.h"

class CO2Sensor {
public:
    CO2Sensor();
    void begin();
    void readCO2();

private:
    SensirionI2CScd4x scd4x;
    unsigned int interval;
    unsigned int last_measurement;
};

#endif
