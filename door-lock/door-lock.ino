//RFID Door Lock System
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 4
#define RST_PIN 2
#define MISO_PIN  6  //GPIO27
#define MOSI_PIN  7  //GPIO26
#define SCK_PIN   5
#define BUZZER 2 
#define lock 3
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
void setup()
{
Serial.begin(9600); // Initiate a serial communication
SPI.begin(); // Initiate SPI bus
mfrc522.PCD_Init(); // Initiate MFRC522
pinMode(BUZZER, OUTPUT);
noTone(BUZZER);
pinMode(lock,OUTPUT);
}
void loop()
{
  digitalWrite(lock,HIGH);
// Look for new cards
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
if ((content.substring(1) == "5D EE 48 62")||(content.substring(1) == "5B 9F C2 3B"))
{
Serial.println("Access Granted");
Serial.println();
delay(500);
tone(BUZZER, 1000); // Play a 1000 Hz tone
delay(300); // Wait for 0.3 second
noTone(BUZZER); // Stop the tone
delay(100); // Wait for 0.1 second
tone(BUZZER, 1000); // Play a 1000 Hz tone
delay(200); // Wait for 0.2 second
noTone(BUZZER); // Stop the tone
delay(100); // Wait for 0.1 second
digitalWrite(lock,LOW);
delay(3000);
digitalWrite(lock,HIGH);
tone(BUZZER, 1000); // Play a 1000 Hz tone
delay(300); // Wait for 0.3 second
noTone(BUZZER); // Stop the tone
delay(100); // Wait for 0.1 second
tone(BUZZER, 1000); // Play a 1000 Hz tone
delay(200); // Wait for 0.2 second
noTone(BUZZER); // Stop the tone
delay(100); // Wait for 0.1 second
delay(100);
}
else
{
  Serial.println("Access Denied");
  Serial.println();
  digitalWrite(lock,HIGH);
  tone(BUZZER, 1000); // Play a 1000 Hz tone
  delay(1500); // Wait for 1 second
  noTone(BUZZER); // Stop the tone
  delay(1000); // Wait for 1 second
}
}