#include <Wire.h>
#include <MFRC522.h>
#include <FirebaseESP8266.h>
#include <FirebaseJson.h>
#include <Servo.h>

#define SS_PIN 2  // SDA pin
#define RST_PIN 8 // RST pin
#define BUZZER_PIN 4 // Change 12 to the actual GPIO number for D6 on your NodeMCU
#define SERVO_PIN 3 // Change 14 to the actual GPIO number for D5 on your NodeMCU

MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo servo;

#define FIREBASE_HOST "iot-project-4e03a-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "F6mTwUKPRYNFl7PHKR02c6PVdCTLB2gDp0G9mWBh"

const char* ssid = "VIRAT KOHLI";
const char* password = "123456789";

void beep(int beeps = 1);
void controlServo(bool open);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(BUZZER_PIN, OUTPUT);
  servo.attach(SERVO_PIN);
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.println("Card detected!");

    // Get the RFID card UID
    String cardUID = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      cardUID += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
      cardUID += String(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println("Card UID: " + cardUID);

    // Check UID against Firebase data
    if (checkUIDWithFirebase(cardUID)) {
      // Student is recognized
      // Handle attendance logic here
      beep(); // Single beep
      controlServo(true); // Open the servo
      delay(5000); // Wait for 5 seconds
      controlServo(false); // Close the servo
    } else {
      // Student not recognized
      beep(2); // Double beep
    }

    delay(1000); // Delay to avoid multiple reads
  }
}

bool checkUIDWithFirebase(String uid) {
  FirebaseJson json;
  FirebaseData firebaseData;

  // Construct the path to the student's data in Firebase
  String path = "/students/" + uid;

  if (Firebase.get(firebaseData, path)) {
    // Check if the student exists in the database
    if (firebaseData.dataType() == "string") {
      Serial.println("Student found!");
      return true;
    } else {
      Serial.println("Student not found!");
      return false;
    }
  } else {
    Serial.println("Firebase error: " + firebaseData.errorReason());
    return false;
  }
}

void beep(int beeps) {
  for (int i = 0; i < beeps; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200); // Adjust duration of beep
    digitalWrite(BUZZER_PIN, LOW);
    delay(200); // Adjust duration of silence between beeps
  }
}

void controlServo(bool open) {
  if (open) {
    servo.write(90); // Open position, adjust as needed
  } else {
    servo.write(0); // Close position, adjust as needed
  }
  delay(500); // Adjust the delay as needed to allow the servo to move
}
