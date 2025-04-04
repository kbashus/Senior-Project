int light_sensor = A3; 
 
int value = 0;
float voltage;

void setup() {
Serial.begin(9600); //begin Serial Communication
}
 
void loop() {
  int raw_light = analogRead(light_sensor); // read the raw value from light_sensor pin (A3)
  int light = map(raw_light, 0, 1023, 0, 100); // map the value from 0, 1023 to 0, 100
  
  value = analogRead(A0);
  voltage = value * 5.0/1023;
  Serial.print("Voltage= ");
  Serial.println(voltage);
  
  Serial.print("Light level: "); 
  Serial.println(light); // print the light value in Serial Monitor
 
  delay(1000); // add a delay to only read and print every 1 second
}