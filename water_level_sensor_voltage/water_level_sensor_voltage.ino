// Sensor pins
#define sensorPower 7
#define sensorPin A5

// Thresholds
int upperThreshold = 1016;
int lowerThreshold = 1023;

// Value for storing water level
int val = 0;


int value = 0;
float voltage;

void setup() {
	// Set D7 as an OUTPUT
	pinMode(sensorPower, OUTPUT);
	
	// Set to LOW so no power flows through the sensor
	digitalWrite(sensorPower, LOW);
	
	Serial.begin(9600);
}

void loop() {
	//get the reading from the function below and print it
	int level = readSensor();
  
	if(level <= 1023 && level >= 1021){
      Serial.println("Water level: LOW ");
  } else if(level < 1021 && level > 1018){
      Serial.println("Water level: MED ");
  } else{
    Serial.println("Water level: HIGH ");
  }

  //int adjustedLevel = map(level, 1023, 880, 0, 100); // map the value from 0, 1023 to 0, 100
	//Serial.println(level);
	
	delay(1500);
}

//This is a function used to get the reading
int readSensor() {
	digitalWrite(sensorPower, HIGH);	// Turn the sensor ON
	delay(10);							// wait 10 milliseconds
	val = analogRead(sensorPin);		// Read the analog value from sensor
	digitalWrite(sensorPower, LOW);		// Turn the sensor OFF
  voltage = val * 5.0/1023;
  Serial.print("Voltage= ");
  Serial.println(voltage);

	return val;							// send current reading
}