// Include the necessary libraries
#include <SoftwareSerial.h>
#include <Servo.h>

// Define Bluetooth module pins
#define BT_RX 13
#define BT_TX 12

// Define motor driver 1 pins
#define ENA 5
#define IN1 6
#define IN2 7

// Define motor driver 2 pins
#define ENB 10
#define IN3 8
#define IN4 9

// Define flame sensor pin
#define FLAME_SENSOR A0

// Define water pump and servo motor pins
#define WATER_PUMP 3
#define SERVO_MOT 2

// Create a SoftwareSerial object for Bluetooth communication
SoftwareSerial bluetooth(BT_RX, BT_TX);

// Create a Servo object for controlling the servo motor
Servo servoMotor;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Initialize Bluetooth communication
  bluetooth.begin(9600);

  // Motor driver 1 setup
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Motor driver 2 setup
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Flame sensor and water pump setup
  pinMode(FLAME_SENSOR, INPUT);
  pinMode(WATER_PUMP, OUTPUT);

  // Servo motor setup
  servoMotor.attach(SERVO_MOT);

  // Turn off both motors, water pump, and servo motor initially
  digitalWrite(ENA, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  
  digitalWrite(ENB, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  digitalWrite(WATER_PUMP, LOW);

  // Set the initial position of the servo motor
  servoMotor.write(0);
}
char terminalread;
void loop() {
  // Check for incoming Bluetooth data
  // if (bluetooth.available() > 0) {
  //   char command = bluetooth.read();

  //   // Process Bluetooth commands
  //   switch (command) {
  //     case 1: 
  //       forward();
  //       break;
  //     case 2:
  //       back();
  //       break;
  //     case 3: 
  //       left();
  //       break;
  //     case 4:
  //       right();
  //       break;
  //     case 5: 
  //       stop();
  //       break;
  //     case 6: 
  //       checkFlameSensor();
  //       break;
  //   }
  // }
  if(Serial.available()>0){
    terminalread=Serial.read();
    delay(2);
    if(terminalread=='forward'){
      forward();
    }
    if(terminalread=='back'){
      back();
    }
    if(terminalread=='left'){
      left();
    }
    if(terminalread=='right'){
      right();
    }
    if(terminalread=='stop'){
      stop();
    }
  }
}
void forward(){
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, LOW);
}
void right(){
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
}
void left(){
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN4, LOW);
}
void back(){
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN3, LOW);
}
void stop(){
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN3, LOW);
}
void checkFlameSensor() {
  int flameValue = analogRead(FLAME_SENSOR);

  // Adjust the flame threshold based on your sensor and environment
  if (flameValue > 200) {
    digitalWrite(WATER_PUMP, HIGH);

    // Rotate the servo motor from 0 to 180 degrees
    for (int i = 0; i <= 180; i ++) {
      servoMotor.write(i);
      delay(15);  // Adjust the delay as needed
    }
      // Rotate the servo motor from 180 to 0 degrees
    for (int i = 180; i >= 0; i--) {
      servoMotor.write(i);
      delay(15);  // Adjust the delay as needed
  }} else {
    digitalWrite(WATER_PUMP, LOW);
    servoMotor.write(0);
    }
  }

