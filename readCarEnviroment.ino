#include "DHT.h"
#include <stdbool.h>

// Constants
#define BAUD 9600
#define DHTPIN 2
#define DHTTYPE DHT22
#define DUSTPIN A0
#define LDRPIN 4

// Sensor objects
DHT dht(DHTPIN, DHTTYPE);

// Conversion factors (replace with actual values for your sensor)
#define DUST_CONVERSION_FACTOR 120000.0
#define DUST_OFFSET 0.0356
#define DUST_SCALE 0.035

void setup() {
    Serial.begin(BAUD);
    dht.begin();
    pinMode(DUSTPIN, INPUT);
    pinMode(LDRPIN, INPUT);
}

bool readDHT(float *humidity, float *temperature) {
    *humidity = dht.readHumidity();
    *temperature = dht.readTemperature();

    if (isnan(*humidity) || isnan(*temperature)) {
        Serial.println("Failed to read from DHT sensor!");
        return false;
    }
    
    Serial.println("Successfully read from DHT sensor!");
    return true;
}

bool readDust(float *dust) {
    float rawValue = analogRead(DUSTPIN);
    *dust = (rawValue / 1024.0 - DUST_OFFSET) * DUST_CONVERSION_FACTOR * DUST_SCALE;

    if (rawValue < 0) {
        Serial.println("Failed to read from dust sensor!");
        return false;
    }
    
    Serial.println("Successfully read from dust sensor!");
    return true;
}

bool readLuminosity(float *luminosity) {
    *luminosity = digitalRead(LDRPIN);

    Serial.println("Successfully read from photoresistor!");
    return true;
}

void printSensorValue(const char* label, float value, const char* unit) {
    Serial.print(label);
    Serial.print(": ");
    Serial.print(value);
    Serial.print(" ");
    Serial.println(unit);
    Serial.println();
}

void loop() {
    float humidity = 0;
    float temperature = 0;
    float dust = 0;
    float luminosity = 0;

    if (readDHT(&humidity, &temperature)) {
        printSensorValue("Humidity", humidity, "%");
        printSensorValue("Temperature", temperature, "*C");
    }

    if (readDust(&dust)) {
        printSensorValue("Dust", dust, "ug/m3");
    }

    if (readLuminosity(&luminosity)) {
        printSensorValue("Luminosity", luminosity, "");
    }
    
    Serial.println("==========");
    Serial.println();

    delay(1000);
}