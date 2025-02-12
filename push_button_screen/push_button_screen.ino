#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#include <DHT.h>
#include "DHT.h"             // Library for DHT sensors

#define BUTTON_PIN 3
#define dhtPin 5            // data pin
#define dhtType DHT22      // DHT 22 (AM2302)

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

DHT dht(dhtPin, dhtType);    // Initialise the DHT library

float humidityVal;           // humidity
float tempValC;              // temperature in degrees Celcius
float tempValF;              // temperature in degrees Fahrenheit
float heatIndexC;            // windchill in degrees Celcius
float heatIndexF;            // windchill in degrees Fahrenheit

int count = 0;

//volatile int buttonState;
volatile bool buttonPressed = false;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  dht.begin();               // start with reading the DHT sensor

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonPress, RISING);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  
}


void buttonPress(){
  //buttonState = digitalRead(BUTTON_PIN);
  buttonPressed = true;
  
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
  

  // Print all values to the serial monitor
  // \t prints a tab character
  // Serial.print("Humidity: ");
  // Serial.print(humidityVal);
  // Serial.println(" %");

  // Serial.print("Temperature: ");
  // Serial.print(tempValC);
  // Serial.print(" °C ");
  // Serial.print(tempValF);
  // Serial.println(" °F");

  // display.clearDisplay();
  // display.display(); 

  // do{
     //byte buttonState = digitalRead(BUTTON_PIN);
    

  //   if (buttonState == LOW) {
  //       Serial.println("Button is not pressed");
  //   }
  //   else if (buttonState == HIGH) {
  //     Serial.println("Button is pressed");
  //     display.setTextSize(1.5);
  //     display.setTextColor(WHITE);
  //     display.setCursor(0, 10);
  //     // Display static text
  //     display.print("Temperature:");
  //     display.print(tempValF);
  //     display.print((char)247); // degree symbol 
  //     display.println(" F");
  //     display.display(); 

  //     display.setTextSize(1.5);
  //     display.setTextColor(WHITE);
  //     display.setCursor(0, 20);
  //     // Display static text
  //     display.print("Humidity:");
  //     display.print(humidityVal);
  //     display.print((char)247); // percentage symbol
  //     display.display(); 


  //     delay(60000);
  //     display.clearDisplay();
  //     display.display(); 
  //     count += 1;
  //     Serial.println(count);
  //     }
  //   delay(100);
  // } while (count < 2);

  display.clearDisplay();
  display.display(); 

  if (buttonPressed) {
    display.clearDisplay();
    display.setTextSize(1.5);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    
    // Display Temperature
    display.print("Temperature:");
    display.print(tempValF);
    display.print((char)247);  // Degree symbol
    display.println(" F");

    // Display Humidity
    display.setCursor(0, 30);
    display.print("Humidity:");
    display.print(humidityVal);
    display.print((char)247);  // Percentage symbol
    display.display();
    delay(60000);
    display.clearDisplay();
    display.display(); 
    
    buttonPressed = false;  // Reset the button flag
  }

}


