int sensorPin = A0; // select the input pin for LDR
int sensorValue = 0; // variable to store the value coming from the sensor
int inPin = 2;         // the number of the input pin
int outPin = 13;       // the number of the output pin for the startButton
int sensorOutPin = 12; // the number of the output pin for the sensor
int state = HIGH;      // the current state of the output pin
int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin

					   // the follow variables are long's because the time, measured in miliseconds,
					   // will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 200;
// variables will change:
void setup() {
	Serial.begin(9600); //sets serial port for communication
	pinMode(inPin, INPUT_PULLUP);
	pinMode(outPin, OUTPUT);
}
void loop() {
	// -----------Button on/off------------
	reading = digitalRead(inPin);
	// if the input just went from LOW and HIGH and we've waited long enough
	// to ignore any noise on the circuit, toggle the output pin and remember
	// the time
	if (reading == LOW && previous == HIGH && millis() - time > debounce) {
		if (state == HIGH)
		{
			state = LOW;
			Serial.println("OFF");
		}
		else
		{
			state = HIGH;
			Serial.println("ON");
		}
		time = millis();
	}

	digitalWrite(outPin, state);

	previous = reading;
	//---------- Sensor && output led------------------  
	if (state == HIGH)
	{
		sensorValue = analogRead(sensorPin); // read the value from the sensor
		Serial.println(sensorValue); //prints the values coming from the sensor on the screen
		delay(100);
		if (sensorValue > 500) {
			digitalWrite(sensorOutPin, HIGH);
			Serial.println("Closing...");
		}
		else {
			digitalWrite(sensorOutPin, LOW);
			Serial.println("Opening...");
		}
	}
	else
	{
		digitalWrite(sensorOutPin, LOW);
		Serial.println("System is OFF");
	}
	//----------------------------------------------
}