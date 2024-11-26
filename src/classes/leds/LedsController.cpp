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
    this->light = false;
    this->temp = false;
    this->humidity = false;
    this->CO2 = false;
}

void LedsController::setConnection(String connection_state){
    this->connection_state = connection_state;
    this->show();
}

void LedsController::setLight(bool state){
    this->light = state;
    this->show();
}
void LedsController::setTemp(bool state){
    this->temp = state;
    this->show();
}
void LedsController::setHumidity(bool state){
    this->humidity = state;
    this->show();
}

void LedsController::setCO2(bool state){
    this->CO2 = state;
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

    leds[1] = light ? 0x00ff00 : 0xff0000;
    leds[2] = temp ? 0x00ff00 : 0xff0000;
    leds[3] = humidity ? 0x00ff00 : 0xff0000;
    leds[4] = CO2 ? 0x00ff00 : 0xff0000;

    FastLED.show();
}