#include "LedsController.h"
#include <FastLED.h>
#include <Arduino.h>

#define NUM_LEDS 5
#define DATA_PIN 13

CRGB leds[NUM_LEDS];

LedsController::LedsController(){
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

    for(int i = 0; i < 5; i++){
        leds[i] = 0xFFFF00;
    }

    this->connection_state = "IDLE";
    this->light = -9999;
    this->temp = -9999;
    this->humidity = -9999;
    this->CO2 = -9999;
}


void LedsController::setCO2(float state){
    this->CO2 = state;
    this->show();
}
void LedsController::setLight(float state){
    this->light = state;
    this->show();
}
void LedsController::setTemp(float state){
    this->temp = state;
    this->show();
}
void LedsController::setHumidity(float state){
    this->humidity = state;
    this->show();
}
void LedsController::setConnection(String connection_state){
    this->connection_state = connection_state;
    this->show();
}

void LedsController::show(){

    if(connection_state == "IDLE"){
        leds[0] = 0xff0000;
    }
    else if(connection_state == "CONNECTING"){
        leds[0] = 0x0000ff;
    }
    else{
        leds[0] = 0x00ff00;
    }

    if(light != 9999){
        leds[1] = (light != -9999) ? 0x00ff00 : 0xff0000;
    }
    if(CO2 != 9999){
        leds[2] = (CO2 != -9999) ? 0x00ff00 : 0xff0000;
    }
    if(temp != 9999){
        leds[3] = (temp != -9999) ? 0x00ff00 : 0xff0000;
    }
    if(humidity != 9999){
        leds[4] = (humidity != -9999) ? 0x00ff00 : 0xff0000;
    }



    FastLED.show();
}