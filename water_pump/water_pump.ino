// MOTOR 1
#define IN1 10
#define IN2 9

void setup() {
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
}
void loop() {
  
 // motor 1 run 50% speed
 
  analogWrite(IN1,255/2);
  digitalWrite(IN2, LOW);
  delay(9000);

// motor 1 stop for 3 seconds
  digitalWrite(IN1,LOW);
  digitalWrite(IN2, LOW);
  delay(3000);
}