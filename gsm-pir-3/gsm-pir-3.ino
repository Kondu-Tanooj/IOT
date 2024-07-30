#include <SoftwareSerial.h>

// PIR Sensor
const int pirPin = 2; // Change to the actual pin number where the PIR sensor is connected

// SIM800L GSM Module
SoftwareSerial gsmSerial(7, 8); // RX, TX. Change to the actual pin numbers where the SIM800L module is connected
String phoneNumber = "+918897720549"; // Replace with the phone number you want to call

void setup() {
  Serial.begin(9600);
  gsmSerial.begin(9600);
  pinMode(pirPin, INPUT);

  // Wait for the SIM800L module to initialize
  delay(1000);
  
  // Enable AT commands
  gsmSerial.println("AT");
  delay(1000);
}

void loop() {
  if (digitalRead(pirPin) == HIGH) {
    Serial.println("Motion detected!");

    // Make a call
    makeCall();

    // Wait to avoid multiple calls for continuous motion
    delay(10000); // Adjust the delay as needed
  }
}

void makeCall() {
  Serial.println("Making a call...");

  // Dial the phone number
  gsmSerial.print("ATD");
  gsmSerial.print(phoneNumber);
  gsmSerial.println(";");

  delay(20000); // Adjust the delay based on the desired call duration

  // End the call
  gsmSerial.println("ATH");
}
