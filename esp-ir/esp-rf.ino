
int irSensorPin1 = D5;
int irSensorPin2 = D4;
void setup() {
  Serial.begin(9600);
  pinMode(irSensorPin1, INPUT);
  pinMode(irSensorPin2, INPUT);
}
void loop() {
  int irSensorValue1 = digitalRead(irSensorPin1);
  int irSensorValue2 = digitalRead(irSensorPin2);
  if (irSensorValue1 == LOW) {
    // Serial.println("Object detected by Sensor 1!");
      if (irSensorValue2 == LOW) {
    Serial.println("IN");
  }
  }
  if (irSensorValue2 == LOW) {
    // Serial.println("Object detected by Sensor 1!");
      if (irSensorValue1 == LOW) {
    Serial.println("OUT");
  }
  }
  delay(500);
}
