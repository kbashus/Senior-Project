#define RELAY_PIN 47
#define light_sensor A11


void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);

}

void loop() {
 int raw_light = analogRead(light_sensor);
 int light = map(raw_light, 0, 1023, 0, 100);

 if(light < 33){
  digitalWrite(RELAY_PIN, HIGH); // turn on
 } else{
  digitalWrite(RELAY_PIN, LOW);
 }

}
