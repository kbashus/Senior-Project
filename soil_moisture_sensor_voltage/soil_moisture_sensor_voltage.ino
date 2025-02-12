


const int dry = 513; // value for dry sensor
const int wet = 260; // value for wet sensor

int value = 0;
float voltage;


void setup()
{ 
  Serial.begin(9600);
}

void loop()
{
  int sensorVal = analogRead(A0);

  // Sensor has a range of 260 to 502
  // We want to translate this to a scale or 0% to 100%
  // More info: https://www.arduino.cc/reference/en/language/functions/math/map/
  int percentageHumidity = map(sensorVal, wet, dry, 100, 0); 

  voltage = sensorVal * 5.0/1023;
  Serial.print("Voltage= ");
  Serial.println(voltage);

  //Serial.print(percentageHumidity);
  //Serial.println("%");

  if (percentageHumidity >= 67 && percentageHumidity <= 100) {
    Serial.println((String) "Wet: " + percentageHumidity + "%");
  } else if (percentageHumidity >= 34 && percentageHumidity < 67) {
    Serial.println((String) "Moist: " + percentageHumidity + "%");
  } else {
    Serial.println((String) "Dry: " + percentageHumidity + "%");
  }
  
  delay(12000);
}