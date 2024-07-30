#include <Wire.h> 
#include <hd44780.h>          // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h>  // i2c expander i/o class header

hd44780_I2Cexp lcd;  // declare lcd object: auto locate & config exapander chip

void setup() {
  lcd.begin(16, 2);  // initialize 16x2 LCD
  lcd.backlight();   // turn on LCD backlight
  lcd.setCursor(0, 0);
  lcd.print("Hello, NodeMCU!");
  lcd.setCursor(0, 1);
  lcd.print("LCD is working!");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Click-RedButton");
  lcd.setCursor(0,1);
  lcd.print(" Entry/Report ");

}

void loop() {
  // Nothing in loop for this example
}
/*
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 

LiquidCrystal_I2C lcd(0x27, 16, 2);  

void setup() {
  lcd.init();                      
  lcd.backlight();                 
  lcd.setCursor(0, 0);            
  lcd.print("Hello, NodeMCU!");   
  lcd.setCursor(0, 1);            
  lcd.print("LCD is working!");   
}

void loop() {
  // Nothing in loop for this example
}
*/