#ifndef LEDSCONTROLLER_H
#define LEDSCONTROLLER_H

#include <Arduino.h>

class LedsController {
public:

public:
    LedsController();
    
    void setConnection(String connection_state);
    void setLight(bool state);
    void setTemp(bool state);
    void setHumidity(bool state);
    void setCO2(bool state);

    void show();

private:

    String connection_state;
    bool light;
    bool temp;
    bool humidity;
    bool CO2;

};

#endif
