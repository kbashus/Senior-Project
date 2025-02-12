#include <DHT.h>

#include "DHT.h"             // Library for DHT sensors

#define dhtPin 5            // data pin


#define dhtType DHT22      // DHT 22 (AM2302)

DHT dht(dhtPin, dhtType);    // Initialise the DHT library

float humidityVal;           // humidity
float tempValC;              // temperature in degrees Celcius
float tempValF;              // temperature in degrees Fahrenheit
float heatIndexC;            // windchill in degrees Celcius
float heatIndexF;            // windchill in degrees Fahrenheit

int value = 0;
float voltage;

void setup() {
  Serial.begin(9600);        // Initialise the serial monitor
  dht.begin();               // start with reading the DHT sensor
}

void loop() {

  humidityVal = dht.readHumidity();        // get the humidity from the DHT sensor
  tempValC = dht.readTemperature();        // get the temperature in degrees Celcius from the DHT sensor
  tempValF = dht.readTemperature(true);    // get the temperature in degrees Fahrenheit from the DHT sensor

  // Check if all values are read correctly, if not try again and exit loop()
  if (isnan(humidityVal) || isnan(tempValC) || isnan(tempValF)) {
    Serial.println("Reading DHT sensor failed!");

    // end the loop() function
    return;
  }

  value = analogRead(A0);
  voltage = value * 5.0/1023;
  Serial.print("Voltage= ");
  Serial.println(voltage);
  

  // Print all values to the serial monitor
  // \t prints a tab character
  // Serial.print("Humidity: ");
  // Serial.print(humidityVal);
  // Serial.println(" %");

   Serial.print("Temperature: ");
  // Serial.print(tempValC);
  // Serial.print(" °C ");
   Serial.println(tempValF);
  // Serial.println(" °F");
  
  delay(2000);
}