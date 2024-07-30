#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <SoftwareSerial.h>

// Define GSM module connections
#define GSM_RX 10
#define GSM_TX 11

// Define the phone numbers to which you want to send the SMS
#define DESTINATION_NUMBER_1 "+919346311566"  // Replace with the actual phone number
#define DESTINATION_NUMBER_2 "+917981831412"  // Replace with another phone number
#define DESTINATION_NUMBER_3 "+919110523264"  // Replace with yet another phone number

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
SoftwareSerial mySerial(GSM_RX, GSM_TX);

// Constants for tap detection
const int tapThreshold = 15; // Adjust this threshold according to your requirements
const unsigned long tapInterval = 10; // Minimum time between tap detections (milliseconds)
// const unsigned long tapInterval2 = 3000; // Minimum time between tap detections (milliseconds)

// Variables
unsigned long lastTapTime = 0;
int tapCount = 0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  if (!accel.begin()) {
    Serial.println("Could not find a valid ADXL345 sensor, check wiring!");
    while (1);
  }

  // Set the range to 16G
  accel.setRange(ADXL345_RANGE_16_G);

  // // Enable tap detection on the X, Y, and Z axes
  // accel.writeRegister(0x2A, 0x07); // Tap detection control register

  // // Enable tap detection interrupt
  // accel.writeRegister(0x2E, 0x40); // Bit 6: Enable Tap detection

  Serial.println("Tap detection enabled");

  // Initialize GSM module
  initializeGSM();
}

void loop() {
  // Get a new sensor event
  sensors_event_t event;
  accel.getEvent(&event);

  // Calculate total acceleration
  float acceleration = sqrt(event.acceleration.x * event.acceleration.x +
                             event.acceleration.y * event.acceleration.y +
                             event.acceleration.z * event.acceleration.z);

  // Check if the acceleration exceeds the threshold
  if (acceleration > tapThreshold) {
    unsigned long currentTime = millis();

    // Check if enough time has passed since the last tap
    if (currentTime - lastTapTime > tapInterval){
      // if(currentTime - lastTapTime < tapInterval2 ) {
      // sendSMS("Triple tap detected!", DESTINATION_NUMBER_1);
      // sendSMS("Triple tap detected!", DESTINATION_NUMBER_2);
      // sendSMS("Triple tap detected!", DESTINATION_NUMBER_3);
      tapCount++;
       Serial.println("Tap..");
       lastTapTime = currentTime;
    } else {
      tapCount = 1;
    }
    // }

    // If triple tap is detected, send SMS to designated numbers
    if (tapCount == 3) {
      Serial.println("3 Tapping");
      sendSMS("Triple tap detected!", DESTINATION_NUMBER_1);
      sendSMS("Triple tap detected!", DESTINATION_NUMBER_2);
      sendSMS("Triple tap detected!", DESTINATION_NUMBER_3);
      tapCount = 0; // Reset tap count after sending SMS
      delay(5000); // Avoid multiple messages in quick succession
    }
  }

  delay(50); // Adjust the delay based on your requirements
}

void initializeGSM() {
  mySerial.println("AT");
  delay(1000);

  mySerial.println("AT+CMGF=1"); // Set SMS mode to text
  delay(1000);

  mySerial.println("AT+CNMI=2,2,0,0,0"); // New SMS notification settings
  delay(1000);
}

void sendSMS(const char* message, const char* destinationNumber) {
  mySerial.print("AT+CMGS=\"");
  mySerial.print(destinationNumber);
  mySerial.println("\"");
Serial.println(destinationNumber);
  delay(500);

  mySerial.print(message);
  mySerial.write('\r');
Serial.println(message);
  delay(500);

  mySerial.write(26); // Send Ctrl+Z to indicate the end of the message
  delay(500);
}
