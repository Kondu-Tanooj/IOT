void setup() {
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {
  String incomingSentence = "";

  // Check if data is available to read
  while (Serial.available() > 0) {
    // Read the incoming byte:
    char incomingByte = Serial.read();

    // Check if we receive new line character
    if(incomingByte == '\n') {
      break; // Break the loop if new line character is found
    }

    // Append the incoming byte to the incomingSentence
    incomingSentence += incomingByte;

    // Delay to allow buffer to fill up with next character
    delay(10);
  }

  // If incomingSentence is not empty then print it
  if (incomingSentence.length() > 0) {
    Serial.print("I received: ");
    Serial.println(incomingSentence);
  }
}
