#include <Arduino.h>

#include <DHT.h>

#include <Wire.h>
#include <BH1750.h>

//Light
BH1750 lightMeter;

// Temp & Humidity
// #define DHTPIN 23
// #define DHTTYPE DHT22
// DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);

    Wire.begin(21, 22);
    lightMeter.begin();

//   dht.begin();
}

void loop() {
  delay(2000);

//   runTempHumidity();
    float lux = lightMeter.readLightLevel();
    if (lux < 0) {
        Serial.println("Failed to read from BH1750");
    } else {
        Serial.print("Light Level: ");
        Serial.print(lux);
        Serial.println(" lx");
    }
}

void runLight(){
    float lux = lightMeter.readLightLevel();
    if (lux < 0) {
        Serial.println("Failed to read from BH1750");
    } else {
        Serial.print("Light Level: ");
        Serial.print(lux);
        Serial.println(" lx");
    }
}
void runTempHumidity(){
    // float h = dht.readHumidity();
    // float t = dht.readTemperature();

    // if (isnan(h) || isnan(t)) {
    //     Serial.println("Failed to read from DHT sensor!");
    //     return;
    // }

    // Serial.print("Humidity: ");
    // Serial.print(h);
    // Serial.print("%  Temperature: ");
    // Serial.print(t);
    // Serial.println("°C");
}