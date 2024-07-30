// Define the pins for the ultrasonic sensor
const int trigPin = 10; // Trig pin
const int echoPin = 9; // Echo pin
// const int led = 13;
// const int pin = 2;
// Variables to store distance and duration
long duration;
int distanceCM;
// int count=0;
void setup() {
  // Initialize the Serial Monitor
  Serial.begin(9600);
  // pinMode(pin, INPUT);
  // Define the ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // pinMode(led, OUTPUT);
}

void loop() {
  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigger pin high for 10 microseconds to trigger the sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // int irSensorValue1 = digitalRead(pin);
  // Measure the duration of the pulse on the echo pin
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  distanceCM = duration * 0.034 / 2;
  delay(500); // Adjust the delay time as needed
  Serial.println(distanceCM);

}
