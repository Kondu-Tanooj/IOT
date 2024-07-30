#include <Wire.h>  // Include the Wire library for I2C
#include <LiquidCrystal_I2C.h>  // Include the LiquidCrystal_I2C library

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD address to 0x27 for a 16 chars and 2 line display

char message[] = "0123456789abcdefghij";  // Message to display
int messageLength;  // Variable to store the length of the message
int lcdWidth = 16; // LCD width

void setup() {
  lcd.init();  // Initialize the LCD
  lcd.backlight();  // Turn on the backlight
  lcd.setCursor(0, 0);  // Set cursor to first column of first row
}

void loop() {
  int messageLength;  // Variable to store the length of the message
int lcdWidth = 16; // LCD width
    messageLength = strlen(message);  // Get the length of the message

  // Print the message repeatedly with scrolling effect
  for (int i = 0; i < messageLength + lcdWidth; i++) {
    lcd.clear();  // Clear the LCD
    // Calculate the starting index for the portion of the message to print
    int startIndex = i < messageLength ? i : i % messageLength;
    // Calculate the length of the portion of the message to print
    int length = min(messageLength - startIndex, lcdWidth);
    lcd.setCursor(0, 0);  // Set cursor to the beginning of the first line
    // Print the portion of the message that fits within the LCD screen width
    lcd.print(String(message).substring(startIndex, startIndex + length));
    
    if (length < lcdWidth) {
      lcd.print(" "); // Print a space to add some space
      lcd.setCursor(length + 1, 0);  // Set cursor to the beginning of the line after the end of the message
      lcd.print(String(message).substring(0, lcdWidth - length - 1));
    }
    delay(400);  // Delay for smooth scrolling
  }
}
