// MOTOR 1
#define IN3 12
#define IN4 11

void setup() {
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);
}
void loop() {
  
 // motor 1 run 50% speed
 
  analogWrite(IN3,255/2);
  digitalWrite(IN4, LOW);
  delay(9000);

// motor 1 stop for 3 seconds
  digitalWrite(IN3,LOW);
  digitalWrite(IN4, LOW);
  delay(3000);
}