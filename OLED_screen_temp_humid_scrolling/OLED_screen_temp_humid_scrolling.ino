#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <stdlib.h>

#include <DHT.h>
#include "DHT.h"             // Library for DHT sensors

#define dhtPin 5            // data pin
#define dhtType DHT22      // DHT 22 (AM2302)

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

char becomes_temp_message[100];
int becomes_temp_message_size;
char tempValF_string[5];

DHT dht(dhtPin, dhtType);    // Initialise the DHT library

float humidityVal;           // humidity
float tempValC;              // temperature in degrees Celcius
float tempValF;              // temperature in degrees Fahrenheit
float heatIndexC;            // windchill in degrees Celcius
float heatIndexF;            // windchill in degrees Fahrenheit

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  dht.begin();               // start with reading the DHT sensor

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.setTextWrap(false);
  delay(2000);
  display.clearDisplay();
  
}

void loop() {
   humidityVal = dht.readHumidity();        // get the humidity from the DHT sensor
  tempValC = dht.readTemperature();        // get the temperature in degrees Celcius from the DHT sensor
  tempValF = dht.readTemperature(true);    // get the temperature in degrees Fahrenheit from the DHT sensor

  dtostrf(tempValF, -3, 2,tempValF_string);
  strcpy(becomes_temp_message, "Temperature:");
  strcat(becomes_temp_message, tempValF_string);
  //strcat(becomes_temp_message, (char)247); //not working 
  strcat(becomes_temp_message, " F");

  becomes_temp_message_size = sizeof(becomes_temp_message);

  int tempValF_size = sizeof(tempValF_string);

  // Check if all values are read correctly, if not try again and exit loop()
  if (isnan(humidityVal) || isnan(tempValC) || isnan(tempValF)) {
    Serial.println("Reading DHT sensor failed!");

    // end the loop() function
    return;
  }


  display.setTextSize(5);
  display.setTextColor(WHITE);

  for (int i = 0; i <= becomes_temp_message_size; i++){
    display.setCursor(0, 15);
    display.print(becomes_temp_message+i);
    display.display();
    delay(1000);
    display.clearDisplay();
    display.display();
  }
  //display.setCursor(0, 10);
  // Display static text
  //display.print("Temperature:");
  //display.print(tempValF);
  //display.print((char)247); // degree symbol 
 // display.println(" F");
  //display.display(); 

  // display.setTextSize(1.5);
  // display.setTextColor(WHITE);
  // display.setCursor(0, 20);
  // // Display static text
  // display.print("Humidity:");
  // display.print(humidityVal);
  // display.print((char)247); // percentage symbol
  // display.display(); 
  
  delay(5000);
  display.clearDisplay(); //sort of note doing anything w/o .display()
}