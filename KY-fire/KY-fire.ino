const int flamePin = A0; // Analog pin connected to the flame sensor

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
}

void loop() {
  int sensorValue = analogRead(flamePin); // Read the analog value from the sensor
  Serial.print("Flame Sensor Value: ");
  Serial.println(sensorValue); // Print the sensor value
  
  // You can add logic here to take action based on the sensor value
  // For example, if sensorValue is above a certain threshold, you might trigger an alarm or take other actions
  
  delay(1000); // Delay for 1 second before taking the next reading
}
