#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <MFRC522.h>
#include <SPI.h>
#include <Wire.h> 
#include <hd44780.h>          // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h> 
#define RST_PIN   D3     // Reset pin for MFRC522
#define SS_PIN    D4     // Slave Select pin for MFRC522

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance
hd44780_I2Cexp lcd;
const char* ssid = "Doorlock";
const char* password = "123456780";
const char* serverAddress = "http://192.168.31.228/test/sensor_data_test2.php";
  HTTPClient http;
  WiFiClient client;
void setup() {
  Serial.begin(9600);
  SPI.begin();
  lcd.begin(16, 2);  // initialize 16x2 LCD
  lcd.backlight();
  mfrc522.PCD_Init();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  http.begin(client,serverAddress);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  Serial.println("All setup done");
  lcd.setCursor(0, 0);
  lcd.print("Done");
}
void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Read card UID
    Serial.println("read");
    String uid = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      uid += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
      uid += String(mfrc522.uid.uidByte[i], HEX);
    }
    uid.toUpperCase();
    Serial.println("Card UID: " + uid);
    sendSensorDataToServer(uid);
    delay(500); // Delay a bit to avoid reading multiple times
  }
}

void sendSensorDataToServer(String uid) {
  String data = "sensor1="+uid;

  int httpResponseCode = http.POST(data);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
    // Clear the LCD display
    // Find the position of the "<hr>" delimiter in the response string
    int delimiterIndex = response.indexOf("<hr>");

    // If the delimiter is found
    if (delimiterIndex != -1) {
        // Extract the first part of the response string before the delimiter
        String firstPart = response.substring(0, delimiterIndex);
        // Extract the second part of the response string after the delimiter
        String secondPart = response.substring(delimiterIndex + 4); // +4 to skip "<hr>"

        // Print the first part on the first line of the LCD
        lcd.setCursor(0, 0);
        lcd.print(firstPart);
        
        // Print the second part on the second line of the LCD
        lcd.setCursor(0, 1);
        lcd.print(secondPart);
    }
    // Add a delay after printing on the LCD
    delay(1000); // Adjust as needed
  } else {
    Serial.println("Error on HTTP request");
    // Clear the LCD display
    lcd.clear();
    // Print an error message on the LCD
    lcd.setCursor(0, 0);
    lcd.print("Error: HTTP ");
    lcd.setCursor(0, 1);
    lcd.print("Code ");
    lcd.print(httpResponseCode);
    // Add a delay after printing the error message
    delay(2000); // Adjust as needed
  }
  http.end();
}
