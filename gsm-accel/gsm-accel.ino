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
#define DESTINATION_NUMBER_3 "+919502693004"  // Replace with yet another phone number

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
SoftwareSerial gsmSerial(GSM_RX, GSM_TX);

void setup() {
  Serial.begin(9600);
  gsmSerial.begin(9600);

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
  initializeGSM();
}

void loop() {
  if (detectTripleTap()) {
    sendSMS("Triple tap detected!", DESTINATION_NUMBER_1);
    sendSMS("Triple tap detected!", DESTINATION_NUMBER_2);
    sendSMS("Triple tap detected!", DESTINATION_NUMBER_3);
    delay(5000); // Avoid multiple messages in quick succession
  }

  delay(1000); // Adjust the delay based on your requirements
}

void initializeGSM() {
  gsmSerial.println("AT");
  delay(1000);

  gsmSerial.println("AT+CMGF=1"); // Set SMS mode to text
  delay(1000);

  gsmSerial.println("AT+CNMI=2,2,0,0,0"); // New SMS notification settings
  delay(1000);
}

bool detectTripleTap() {
  int tapCount = 0;
  unsigned long lastTapTime = 0;

  uint8_t tapStatus = accel.readRegister(0x30); // Tap status register

  if (tapStatus & 0x07) {
    unsigned long currentTime = millis();
    if (currentTime - lastTapTime < 1000) {
      tapCount++;
    } else {
      tapCount = 1;
    }

    lastTapTime = currentTime;

    if (tapCount == 3) {
      return true;
    }
  }

  return false;
}

void sendSMS(const char* message, const char* destinationNumber) {
  gsmSerial.print("AT+CMGS=\"");
  gsmSerial.print(destinationNumber);
  gsmSerial.println("\"");

  delay(500);

  gsmSerial.print(message);
  gsmSerial.write('\r');

  delay(500);

  gsmSerial.write(26); // Send Ctrl+Z to indicate the end of the message
  delay(500);
}
