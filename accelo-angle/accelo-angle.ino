#include <Wire.h> // Include the Wire library (required for I2C communication)
#include <Adafruit_Sensor.h> // Include the Adafruit Sensor library
#include <Adafruit_ADXL345_U.h> // Include the Adafruit ADXL345 library

// Create an ADXL345 instance
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345); // Pass in a unique ID for the sensor.

void setup(void) {
  Serial.begin(9600);
  Serial.println("ADXL345 test");

  if(!accel.begin()) {
    Serial.println("Could not find a valid ADXL345 sensor, check wiring!");
    while(1);
  }

  // Set the range to whatever is appropriate for your project
  accel.setRange(ADXL345_RANGE_16_G);
}

void loop(void) {
  // Get a new sensor event
  sensors_event_t event;
  accel.getEvent(&event);

  // Print the results (acceleration measured in m/s^2)
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.println("  m/s^2 ");

  delay(500);
}
