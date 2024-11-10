#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include <BH1750.h>
#include <Wire.h>

class LightSensor {
public:
    LightSensor();
    void begin();
    void readLight();

private:
    BH1750 lightMeter;
    unsigned int interval;
    unsigned int last_measurement;
};

#endif
