void setup()
{ 
  Serial.begin(9600);
}

void loop()
{
  Serial.println(analogRead(A15));
  delay(100);
}