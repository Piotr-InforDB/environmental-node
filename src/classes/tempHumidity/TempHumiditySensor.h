#ifndef TEMPHUMIDITYSENSOR_H
#define TEMPHUMIDITYSENSOR_H

#include <DHT.h>
#include <Wire.h>

class TempHumiditySensor {
public:
    TempHumiditySensor();
    void begin();
    float readTemp();
    float readHumidity();

private:
    DHT dht;
    float state_temp;
    float state_humidity;

    unsigned int interval;
    unsigned int temp_last_measurement;
    unsigned int humidity_last_measurement;
};

#endif
