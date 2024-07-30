#include <Wire.h>
#include <MFRC522.h>
#include <FirebaseESP8266.h>
#include <FirebaseJson.h>

#define SS_PIN 4  // SDA pin
#define RST_PIN 3 // RST pin
#define BUZZER_PIN 2 // Change to the actual GPIO number for D6 on your NodeMCU

MFRC522 mfrc522(SS_PIN, RST_PIN);

#define FIREBASE_HOST "iot-project-4e03a-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "F6mTwUKPRYNFl7PHKR02c6PVdCTLB2gDp0G9mWBh"

const char* ssid = "VIRAT KOHLI";
const char* password = "123456789";

void beep(int beeps = 1);
bool writeToFirebase(String uid);

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
    if (writeToFirebase(cardUID)) {
      // RFID card UID written to Firebase successfully
      beep(); // Single beep
    } else {
      Serial.println("Failed to write to Firebase.");
    }

    delay(5000); // Delay to avoid multiple reads
  }
}

bool writeToFirebase(String uid) {
  FirebaseJson json;
  FirebaseData firebaseData;

  // Construct the path to store the RFID card UID in Firebase
  String path = "/rfid-uids/" + uid;

  json.add("timestamp", Firebase.getInt(firebaseData, "/.info/serverTimeOffset") + Firebase.getInt(firebaseData, "/.info/serverTime"));
  json.add("uid", uid);

  if (Firebase.set(firebaseData, path, json)) {
    Serial.println("Write to Firebase successful.");
    return true;
  } else {
    Serial.println("Firebase write error: " + firebaseData.errorReason());
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
