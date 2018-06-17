    // defines pins numbers
    const int trigPin = 9;
    const int echoPin = 10;
    // defines variables
    long duration;
    int distance;
    
void setup() {
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    Serial.begin(9600); // Starts the serial communication
    }

void loop() {
  int pressurePin = 0;
  int val = analogRead(pressurePin);      // read the rawADC value.
  float voltage = (float) val / 1023.0 * 5.0;   // voltage at the input pin
  float kPa = ((voltage - 0.135) / 0.0459) + 15;

    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance= duration*0.034/2;
    // Prints the distance on the Serial Monitor
    Serial.print("distance>");
    Serial.print(distance);//distance
    Serial.print(" pressure>");
    Serial.print(kPa);//pressure
    Serial.print(" latitude>");
    Serial.print(-8.021);
    Serial.print(" longitude>");
    Serial.println(110.321);
    delay(100);
}
