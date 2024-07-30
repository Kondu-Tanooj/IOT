//RFID Door Lock System
#include <Wire.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
#define MISO_PIN  12  //GPIO27
#define MOSI_PIN  11  //GPIO26
#define SCK_PIN   13
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
void setup()
{
Serial.begin(9600); // Initiate a serial communication
SPI.begin(); // Initiate SPI bus
mfrc522.PCD_Init(); // Initiate MFRC522
}
void loop()
{
if ( ! mfrc522.PICC_IsNewCardPresent())
{
return;
}
// Select one of the cards
if ( ! mfrc522.PICC_ReadCardSerial())
{
return;
}
Serial.print("UID tag :");
String content= "";
byte letter;
for (byte i = 0; i < mfrc522.uid.size; i++)
{
Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
Serial.print(mfrc522.uid.uidByte[i], HEX);
content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
content.concat(String(mfrc522.uid.uidByte[i], HEX));
}
Serial.println();
Serial.print("Message : ");
content.toUpperCase();
if ((content.substring(1) == "53 A2 82 F6")||(content.substring(1) == "92 C1 E8 1E"))
{
Serial.println("Access Granted");
Serial.println();
delay(1000);
}
else
{
  Serial.println("Access Denied");
  Serial.println();
  delay(1000); // Wait for 1 second
}
}