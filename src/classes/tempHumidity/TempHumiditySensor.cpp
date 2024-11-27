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

    state_temp = -1;
    state_humidity = -1;

}

void TempHumiditySensor::begin() {
    dht.begin();
    temp_last_measurement = millis();
    humidity_last_measurement = millis();
}

float TempHumiditySensor::readTemp() {
    //Verify interval
    unsigned int currentTime = millis();
    unsigned int elapsed = currentTime - temp_last_measurement;
    
    if (elapsed < interval) { return state_temp; }
    
    temp_last_measurement = currentTime;

    //Measure
    float temperature = dht.readTemperature();

    if (isnan(temperature)) {
        state_temp = -1;
    }
    else{
        Serial.print("Temperature: ");
        Serial.print(temperature - 2);
        Serial.println("°C");
        state_temp = temperature - 2.5;
    }

    return state_temp;
}
float TempHumiditySensor::readHumidity(){
    unsigned int currentTime = millis();
    unsigned int elapsed = currentTime - humidity_last_measurement;
    
    if (elapsed < interval) { return state_humidity; }
    
    humidity_last_measurement = currentTime;


    float humidity = dht.readHumidity();
    if(isnan(humidity)){
        state_humidity = -1;
    }
    else{
        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.println("%");
        state_humidity = humidity;
    }
    
    return state_humidity;
}
