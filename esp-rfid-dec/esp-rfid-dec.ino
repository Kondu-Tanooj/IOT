#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN D3
#define SS_PIN D4
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();  // Initialize MFRC522 card.
  Serial.println("Place your NFC card/tag near the RC522 module...");
}

void loop() {
  // Look for new cards.
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards.
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Calculate UID as a single integer value.
  unsigned long uidValue = 0;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uidValue = (uidValue << 8) | mfrc522.uid.uidByte[i];
  }

  // Show UID on serial monitor.
  Serial.print("UID tag : ");
  Serial.println(uidValue);
  delay(1000);
}
