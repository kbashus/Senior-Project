
int soil_sensor = A0; 

const int dry = 513; // value for dry sensor
const int wet = 260; // value for wet sensor

void setup()
{ 
  Serial.begin(9600);
}

void loop()
{
  int sensorVal = analogRead(soil_sensor);

  // Sensor has a range
  // We want to translate this to a scale or 0% to 100%
  // More info: https://www.arduino.cc/reference/en/language/functions/math/map/
  int percentageHumidity = map(sensorVal, wet, dry, 100, 0); 

  //Serial.print(percentageHumidity);
  //Serial.println("%");

  if (percentageHumidity >= 67 && percentageHumidity <= 100) {
    Serial.println((String) "Wet: " + percentageHumidity + "%");
  } else if (percentageHumidity >= 34 && percentageHumidity < 67) {
    Serial.println((String) "Moist: " + percentageHumidity + "%");
  } else {
    Serial.println((String) "Dry: " + percentageHumidity + "%");
  }
  
  delay(120000);
}