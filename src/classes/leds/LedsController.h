#ifndef LEDSCONTROLLER_H
#define LEDSCONTROLLER_H

#include <Arduino.h>

class LedsController {
public:

public:
    LedsController();
    
    void setConnection(String connection_state);
    void setLight(float state);
    void setTemp(float state);
    void setHumidity(float state);
    void setCO2(float state);

    void show();

private:

    String connection_state;
    float light;
    float temp;
    float humidity;
    float CO2;

};

#endif
