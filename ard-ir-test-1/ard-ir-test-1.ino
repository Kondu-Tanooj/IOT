
int irSensorPin1 = D4;
void setup() {
  Serial.begin(9600);
  pinMode(irSensorPin1, INPUT);
}
void loop() {
  int irSensorValue1 = digitalRead(irSensorPin1);
    if (irSensorValue1 == LOW) {
    Serial.println("Object detected by Sensor 1!");
  }/* else {
    Serial.println("No object detected by Sensor 1.");
  }*/
  delay(1000);
}
