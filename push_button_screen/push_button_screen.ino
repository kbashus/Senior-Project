#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Arduino.h>

#include "Talkie.h"
#include "Vocab_US_Large.h" //"temperature", "light", letters //sp2_
#include "Vocab_Special.h" //sp
#include "Vocab_US_TI99.h" //pauses
#include "Vocab_US_Clock.h" //spc_
#include "Vocab_US_Acorn.h" //"F" //spa_
Talkie voice;


#include <DHT.h>
#include "DHT.h"             // Library for DHT sensors

#define BUTTON_PIN_TEMP 3
#define BUTTON_PIN_HUMID 2
#define BUTTON_PIN_SOIL 18
#define BUTTON_PIN_LIGHT 19
#define dhtPin 53            // temp/humid
#define dhtType DHT22      // DHT 22 (AM2302)
#define soil_sensor A15
#define light_sensor A11

// Water pump/ motor
#define IN3 12
#define IN4 11

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
//
char becomes_temp_message[18];
int becomes_temp_message_size;
char tempValF_string[5];
//
char becomes_humid_message[15];
int becomes_humid_message_size;
char humidityVal_string[5];
//
char becomes_soil_message[9];
int becomes_soil_message_size;
//char soilVal_string[3];
char soilVal_string_dry[] = "Dry ";
char soilVal_string_damp[] = "Damp";
char soilVal_string_wet[] = "Wet ";
// 
char becomes_light_message[11];
int becomes_light_message_size;
char lightVal_string_dark[] = "Dark ";
char lightVal_string_dim[] = "Dim  ";
char lightVal_string_light[] = "Light";



DHT dht(dhtPin, dhtType);    // Initialise the DHT library

//temp and humid
float humidityVal;           // humidity
float tempValC;              // temperature in degrees Celcius
float tempValF;              // temperature in degrees Fahrenheit
float heatIndexC;            // windchill in degrees Celcius
float heatIndexF;            // windchill in degrees Fahrenheit

//soil
//int soil_sensor = A15; 
int raw_soil;
int soilVal;
const int dry = 570; // value for dry sensor
const int wet = 303; // value for wet sensor

//light
int raw_light;
int lightVal;

//volatile int buttonState
volatile bool buttonPressedTemp = false;
volatile bool buttonPressedHumid = false;
volatile bool buttonPressedSoil = false;
volatile bool buttonPressedLight = false;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  dht.begin();               // start with reading the DHT sensor

  //motor
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(BUTTON_PIN_TEMP, INPUT_PULLUP);
  pinMode(BUTTON_PIN_HUMID, INPUT_PULLUP);
  //pinMode(BUTTON_PIN_SOIL, INPUT_PULLUP);
  //pinMode(BUTTON_PIN_LIGHT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN_TEMP), buttonPressTemp, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN_HUMID), buttonPressHumid, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN_SOIL), buttonPressSoil, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN_LIGHT), buttonPressLight, RISING);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.setTextWrap(false);
  delay(2000);
  display.clearDisplay();
  display.display();
  
}


void buttonPressTemp(){
  //buttonState = digitalRead(BUTTON_PIN);
  buttonPressedTemp = true;
}
void buttonPressHumid(){
  buttonPressedHumid = true;
}
void buttonPressSoil(){
  buttonPressedSoil = true;
}
void buttonPressLight(){
  buttonPressedLight = true;
}

void loop() {
  //temp and humid read
  humidityVal = dht.readHumidity();        // get the humidity from the DHT sensor
  tempValC = dht.readTemperature();        // get the temperature in degrees Celcius from the DHT sensor
  tempValF = dht.readTemperature(true);    // get the temperature in degrees Fahrenheit from the DHT sensor

  // Check if all values are read correctly, if not try again and exit loop()
  if (isnan(humidityVal) || isnan(tempValC) || isnan(tempValF)) {
    Serial.println("Reading DHT sensor failed!");
    return;
  }

  //soil moisture read
  raw_soil = analogRead(soil_sensor);
  //soilVal = map(raw_soil, wet, dry, 100, 0); 

  //light level read
  raw_light = analogRead(light_sensor); // read the raw value from light_sensor
  //lightVal = map(raw_light, 0, 1023, 0, 100); // map the value from 0, 1023 to 0, 100v
  

  //TEMP
  if (buttonPressedTemp) {
    display.setTextSize(5.5);
    display.setTextColor(WHITE);
    //create string that prints for temp info
    dtostrf(tempValF, -3, 2,tempValF_string);
    strcpy(becomes_temp_message, "Temperature:");
    strcat(becomes_temp_message, tempValF_string);
    //strcat(becomes_temp_message, "\xB0"); //not working 
    strcat(becomes_temp_message, " F");

    becomes_temp_message_size = sizeof(becomes_temp_message);
    int tempValF_size = sizeof(tempValF_string);

  for (int i = 0; i <= becomes_temp_message_size; i++){
    display.setCursor(0, 15);
    display.print(becomes_temp_message+i);
    display.display();
    delay(1000);
    display.clearDisplay();
    display.display();
  }
  // display.drawBitmap(0, 15, degreeSymbolBitmap, 2, 2, WHITE);
  // display.display();
  // display.clearDisplay();
  // display.display();

  buttonPressedTemp = false;  // Reset the button flag
  }

  //HUMID
  else if (buttonPressedHumid) {
    display.setTextSize(5.5);
    display.setTextColor(WHITE);
    //create string that prints for humid info
    dtostrf(humidityVal, -3, 2, humidityVal_string);
    strcpy(becomes_humid_message, "Humidity:");
    strcat(becomes_humid_message, humidityVal_string);
    strcat(becomes_humid_message, "%");

    becomes_humid_message_size = sizeof(becomes_humid_message);
    int humidityVal_size = sizeof(humidityVal);

  for (int i = 0; i <= becomes_humid_message_size; i++){
    display.setCursor(0, 15);
    display.print(becomes_humid_message+i);
    display.display();
    delay(1000);
    display.clearDisplay();
    display.display();
  }

  buttonPressedHumid = false;  // Reset the button flag
  }


  //SOIL
  else if (buttonPressedSoil) {
    display.setTextSize(5.5);
    display.setTextColor(WHITE);
    //create string that prints for soil info
    //dtostrf(soilVal, -1, 0, soilVal_string);

    strcpy(becomes_soil_message, "Soil:");
    //strcat(becomes_soil_message, soilVal_string);
    if (raw_soil < 392) {
      strcat(becomes_soil_message, soilVal_string_wet);
    } else if (raw_soil < 481) {
      strcat(becomes_soil_message, soilVal_string_damp);
    } else  { //if (raw_soil < 570)
      strcat(becomes_soil_message, soilVal_string_dry);
    } 
    //strcat(becomes_soil_message, "%");

    becomes_soil_message_size = sizeof(becomes_soil_message);

    for (int i = 0; i <= becomes_soil_message_size; i++){
    display.setCursor(0, 15);
    display.print(becomes_soil_message+i);
    display.display();
    delay(1000);
    display.clearDisplay();
    display.display();
  }

    buttonPressedSoil = false;
  }

  //LIGHT
  else if (buttonPressedLight) {
    display.setTextSize(5.5);
    display.setTextColor(WHITE);
    //create string that prints for light info
    //dtostrf(lightVal, -1, 0, lightVal_string);
    strcpy(becomes_light_message, "Light:");
    if (raw_light < 10) {
      strcat(becomes_light_message, lightVal_string_dark);
    } else if (raw_light < 200) {
      strcat(becomes_light_message, lightVal_string_dim);
    } else  { //if (raw_light < 500)
      strcat(becomes_light_message, lightVal_string_light);
    } 
    //strcat(becomes_light_message, "%");

    becomes_light_message_size = sizeof(becomes_light_message);

    for (int i = 0; i <= becomes_light_message_size; i++){
    display.setCursor(0, 15);
    display.print(becomes_light_message+i);
    display.display();
    delay(1000);
    display.clearDisplay();
    display.display();
  }

    buttonPressedLight = false;
  } 

  while(raw_soil < 570 && raw_soil > 481){
    //run at 50% speed
    analogWrite(IN3,255/2);
    digitalWrite(IN4, LOW);
    delay(9000);

    //stop
    digitalWrite(IN3,LOW);
    digitalWrite(IN4, LOW);
    delay(10000);
    //recheck
    raw_soil = analogRead(soil_sensor);
  }
      
      /**/

}