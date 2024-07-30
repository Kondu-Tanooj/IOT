#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// Define GSM module connections
#define GSM_RX 10
#define GSM_TX 11

// Define GPS module connections
#define GPS_TX 6
#define GPS_RX 7

#define DESTINATION_NUMBER_1 "+919346311566"  // Replace with the actual phone number
#define DESTINATION_NUMBER_2 "+917981831412"  // Replace with another phone number

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
SoftwareSerial gsmSerial(GSM_RX, GSM_TX);
SoftwareSerial gpsSerial(GPS_RX, GPS_TX); // Create a software serial port for the GPS module

TinyGPSPlus gps;

const int tapThreshold = 15; // Adjust this threshold according to your requirements
const unsigned long tapInterval = 10; // Minimum time between tap detections (milliseconds)

// Variables
unsigned long lastTapTime = 0;
int tapCount = 0;

void setup() {
  Serial.begin(9600);
  gsmSerial.begin(9600);
  gpsSerial.begin(9600); // Initialize the GPS serial connection

  if (!accel.begin()) {
    Serial.println("Could not find a valid ADXL345 sensor, check wiring!");
    while (1);
  }

  // Set the range to 16G
  accel.setRange(ADXL345_RANGE_16_G);

  // Enable tap detection on the X, Y, and Z axes
  accel.writeRegister(0x2A, 0x07); // Tap detection control register

  // Enable tap detection interrupt
  accel.writeRegister(0x2E, 0x40); // Bit 6: Enable Tap detection

  Serial.println("Tap detection enabled");

  // Initialize GSM module
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
    if (currentTime - lastTapTime > tapInterval) {
      tapCount++;
      Serial.println("Tap..");
      lastTapTime = currentTime;
    } else {
      tapCount = 1;
    }

    // If triple tap is detected, send SMS to designated numbers
    if (tapCount == 3) {
      Serial.println("3 Tapping");
      delay(5000);

      // Send SMS to first number with location
      sendSMSWithLocation("Danger!!!", DESTINATION_NUMBER_1);

      // Send SMS to second number with location
      delay(5000); // Adjust delay as needed
      sendSMSWithLocation("Danger!!!", DESTINATION_NUMBER_2);

      Serial.println("Danger!!");
      lastTapTime = 0;
      tapCount = 0;
    }
  }

  // Check for new GPS data
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      // If new GPS data is available, process it
      // You can retrieve latitude and longitude from gps.location object
    }
  }

  delay(50); // Adjust the delay based on your requirements
}

void sendSMSWithLocation(String message, const char* destinationNumber) {
  gsmSerial.println("AT+CMGF=1");    // Sets the GSM Module in Text Mode
  delay(1000);
  gsmSerial.print("AT+CMGS=\"");
  gsmSerial.print(destinationNumber);
  gsmSerial.println("\"");
  delay(1000);
  gsmSerial.print(message);
  delay(1000);
  // Include location data in the SMS message
  gsmSerial.print("Latitude: ");
  gsmSerial.print(gps.location.lat(), 6);
  gsmSerial.print(", Longitude: ");
  gsmSerial.println(gps.location.lng(), 6);
  delay(1000);
  gsmSerial.write(26); // Send Ctrl+Z to indicate the end of the message
  delay(1000);
}
