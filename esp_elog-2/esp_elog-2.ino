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

const char* ssid = "MVGR_SLC";
const char* password = "001010011100";

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
    lcd.print("Connecting....");
  }
  
  Serial.println("Connected to WiFi");
  Serial.println("All setup done");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connected To");
  lcd.setCursor(0,1);
  lcd.print(ssid);
  delay(3000);
  lcd.clear();
}

void loop() {
  if(WiFi.status() != WL_CONNECTED){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Disconnected");
    lcd.setCursor(0,1);
    lcd.print("Searching..");
  } else {
    getcount();
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
      delay(30); // Delay a bit to avoid reading multiple times
    }
  }
}

void getcount() {
  const char* serverAddress = "https://slog.mvgrglug.com/getcount.php"; // Original URL
  HTTPClient http;
  WiFiClientSecure client; // Use WiFiClientSecure for HTTPS
  client.setInsecure(); // Ignore SSL certificate verification (if necessary)
  
  http.begin(client, serverAddress);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded"); 
  String data = "sensor1=send";
  int httpResponseCode = http.POST(data);
  
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("http");
    Serial.println(httpResponseCode);
    Serial.println("response");
    Serial.println(response);
    // Your LCD display code here
    // Clear the LCD display
    lcd.clear();
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
  }
  http.end();
}

void sendSensorDataToServer(String uid) {
  const char* serverAddress = "https://slog.mvgrglug.com/sendid.php"; // Original URL
  HTTPClient http;
  WiFiClientSecure client; // Use WiFiClientSecure for HTTPS
  client.setInsecure(); // Ignore SSL certificate verification (if necessary)
  
  http.begin(client, serverAddress);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String data = "sensor1="+uid;

  int httpResponseCode = http.POST(data);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("http");
    Serial.println(httpResponseCode);
    Serial.println("response");
    Serial.println(response);
   // Clear the LCD display
    lcd.clear();
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
      if(secondPart == " GET Registered"){
        tone(D8, 1000); // Play a 1000 Hz tone
        delay(300); // Wait for 0.3 second
        noTone(D8); // Stop the tone
        delay(500);
        tone(D8, 1000); // Play a 1000 Hz tone
        delay(300); // Wait for 0.3 second
        noTone(D8); // Stop the tone
      } else {
        tone(D8, 1000); // Play a 1000 Hz tone
        delay(300); // Wait for 0.3 second
        noTone(D8); // Stop the tone
      }
      delay(2000); // Adjust as needed
    }
  } else {
    Serial.println("Error on HTTP request");
    // Clear the LCD display
    lcd.clear();
    // Print an error message on the LCD
    lcd.setCursor(0, 0);
    lcd.print("Connection lost");
    lcd.setCursor(0, 1);
    lcd.print("with Database");
    lcd.print(httpResponseCode);
    tone(D8, 1000); // Play a 1000 Hz tone
    delay(300); // Wait for 0.3 second
    noTone(D8); // Stop the tone
    delay(500);
    tone(D8, 1000); // Play a 1000 Hz tone
    delay(300); // Wait for 0.3 second
    noTone(D8); // Stop the tone
    // Add a delay after printing the error message
    delay(1000); // Adjust as needed
  }
}
