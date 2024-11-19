#ifndef TEMPHUMIDITYSENSOR_H
#define TEMPHUMIDITYSENSOR_H

#include <DHT.h>
#include <Wire.h>

class TempHumiditySensor {
public:
    TempHumiditySensor();
    void begin();
    void readTemp();
    void readHumidity();

private:
    DHT dht;
    unsigned int interval;
    unsigned int temp_last_measurement;
    unsigned int humidity_last_measurement;
};

#endif
