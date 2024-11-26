#include "TempHumiditySensor.h"
#include <DHT.h>

#define DHTPIN 23
#define DHTTYPE DHT22

TempHumiditySensor::TempHumiditySensor()
    : dht(DHTPIN, DHTTYPE) 
{
    interval = 5000;
    temp_last_measurement = 0;
    humidity_last_measurement = 0;
}

void TempHumiditySensor::begin() {
    dht.begin();
    temp_last_measurement = millis();
    humidity_last_measurement = millis();
}

bool TempHumiditySensor::readTemp() {
    //Verify interval
    unsigned int currentTime = millis();
    unsigned int elapsed = currentTime - temp_last_measurement;
    
    if (elapsed < interval) { return state_temp; }
    
    temp_last_measurement = currentTime;

    //Measure
    float temperature = dht.readTemperature();

    if (isnan(temperature)) {
        state_temp = false;
    }
    else{
        Serial.print("Temperature: ");
        Serial.print(temperature - 2);
        Serial.println("°C");
        state_temp = true;
    }

    return state_temp;
}
bool TempHumiditySensor::readHumidity(){
    //Verify interval
    unsigned int currentTime = millis();
    unsigned int elapsed = currentTime - humidity_last_measurement;
    
    if (elapsed < interval) { return state_humidity; }
    
    humidity_last_measurement = currentTime;


    float humidity = dht.readHumidity();
    if(isnan(humidity)){
        state_humidity = false;
    }
    else{
        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.println("%");
        state_humidity = true;
    }
    
    return state_humidity;
}
