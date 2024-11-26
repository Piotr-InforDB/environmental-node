#ifndef TEMPHUMIDITYSENSOR_H
#define TEMPHUMIDITYSENSOR_H

#include <DHT.h>
#include <Wire.h>

class TempHumiditySensor {
public:
    TempHumiditySensor();
    void begin();
    bool readTemp();
    bool readHumidity();

private:
    DHT dht;
    bool state_temp;
    bool state_humidity;

    unsigned int interval;
    unsigned int temp_last_measurement;
    unsigned int humidity_last_measurement;
};

#endif
