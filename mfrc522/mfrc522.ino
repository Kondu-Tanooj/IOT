#include <MFRC522.h>
#include <SPI.h>
#include <Wire.h> 
#include <hd44780.h>          // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h>  // i2c expander i/o class header

hd44780_I2Cexp lcd; 

#define RST_PIN   D3     // Reset pin for MFRC522
#define SS_PIN    D4     // Slave Select pin for MFRC522

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);  // initialize 16x2 LCD
  lcd.backlight(); 
  // Initialize SPI bus
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("RFID reader initialized.");
}

void loop() {

  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Read card UID
    String uid = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      uid += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
      uid += String(mfrc522.uid.uidByte[i], HEX);
      // uid += String(mfrc522.uid.uidByte[i], DEC);
    }
    uid.toUpperCase();
    Serial.println("Card UID: " + uid);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Card UID: ");
    lcd.setCursor(0, 1);
    lcd.print(uid);
    delay(1000);
  }
}
