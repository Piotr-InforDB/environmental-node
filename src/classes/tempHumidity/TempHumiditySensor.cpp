#include "TempHumiditySensor.h"
#include <DHT.h>

#define DHTPIN 23
#define DHTTYPE DHT22

TempHumiditySensor::TempHumiditySensor()
    : dht(DHTPIN, DHTTYPE) 
{
    interval = 2500;
    temp_last_measurement = 0;
    humidity_last_measurement = 0;
}

void TempHumiditySensor::begin() {
    dht.begin();
}

void TempHumiditySensor::readTemp() {
    //Verify interval
    unsigned int currentTime = millis();
    unsigned int elapsed = currentTime - temp_last_measurement;
    
    if (elapsed < interval) { return; }
    
    temp_last_measurement = currentTime;

    //Measure
    float temperature = dht.readTemperature();

    if (isnan(temperature)) {
        Serial.println("Handle Temp Error");
    }
    else{
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println("°C");
    }
}
void TempHumiditySensor::readHumidity(){
    //Verify interval
    unsigned int currentTime = millis();
    unsigned int elapsed = currentTime - humidity_last_measurement;
    
    if (elapsed < interval) { return; }
    
    humidity_last_measurement = currentTime;


    float humidity = dht.readHumidity();
    if(isnan(humidity)){
        Serial.print("Handle Humidity Error");
    }
    else{
        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.println("%");
    }
    
}
