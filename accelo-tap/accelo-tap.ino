#include <Wire.h> // Include the Wire library (required for I2C communication)
#include <Adafruit_Sensor.h> // Include the Adafruit Sensor library
#include <Adafruit_ADXL345_U.h> // Include the Adafruit ADXL345 library

// Create an ADXL345 instance
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345); // Pass in a unique ID for the sensor.

// Constants
const int tapThreshold = 15; // Adjust this threshold according to your requirements
const unsigned long tapInterval = 10; // Minimum time between tap detections (milliseconds)

// Variables
unsigned long lastTapTime = 0;

void setup(void) {
  Serial.begin(9600);
  Serial.println("ADXL345 Tap Detection");

  if (!accel.begin()) {
    Serial.println("Could not find a valid ADXL345 sensor, check wiring!");
    while (1);
  }

  // Set the range to whatever is appropriate for your project
  accel.setRange(ADXL345_RANGE_16_G);
}

void loop(void) {
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
      Serial.println("Tap detected!");
      lastTapTime = currentTime;
    }
  }

  delay(50); // Adjust delay time according to your application's requirements
}
