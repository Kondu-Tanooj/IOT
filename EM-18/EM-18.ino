char rf[12];
int c = 0;
void setup() {
  Serial.begin(9600);
}
void loop() {
  if (Serial.available()) {
    c = 0;
    while (Serial.available() && c < 12) {
      char receivedChar = Serial.read();
      if (isAlphaNumeric(receivedChar)) {
        rf[c] = receivedChar;
        c++;
      }
      delay(5);
    }
    rf[c] = '\0';
    Serial.println(rf);
  }
}
