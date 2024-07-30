#include <SoftwareSerial.h>
#include <Servo.h>
Servo servoMotor;
char t;
bool pump;
void setup() {
pinMode(13,OUTPUT);   //left motors  forward
pinMode(12,OUTPUT);   //left motors reverse
pinMode(11,OUTPUT);   //right  motors forward
pinMode(10,OUTPUT);   //right motors reverse
pinMode(9,OUTPUT);    //water pump
pinMode(8,OUTPUT);    //servo motor
pinMode(A0,INPUT);    // Flame sensor
Serial.begin(9600);
servoMotor.attach(8);
servoMotor.write(0);
}
 
void loop() {
if(Serial.available()){
  t = Serial.read();
  Serial.println(t);
}
 
if(t == 'F'){            //move  forward(all motors rotate in forward direction)
  digitalWrite(13,HIGH);
  digitalWrite(11,HIGH);
}
 
else if(t == 'B'){      //move reverse (all  motors rotate in reverse direction)
  digitalWrite(12,HIGH);
  digitalWrite(10,HIGH);
}
  
else if(t == 'L'){      //turn right (left side motors rotate in forward direction,  right side motors doesn't rotate)
  digitalWrite(11,HIGH);
}
 
else  if(t == 'R'){      //turn left (right side motors rotate in forward direction, left  side motors doesn't rotate)
  digitalWrite(13,HIGH);
}

else if(t ==  'W'){    //turn water pump  on or off)
  pump=true;
}
else if(t == 'w'){
  pump=false;
}
 
else if(t == 'S'){      //STOP (all motors stop)
  digitalWrite(13,LOW);
  digitalWrite(12,LOW);
  digitalWrite(11,LOW);
  digitalWrite(10,LOW);
}
delay(100);
if (pump==true){
  int flameValue = analogRead(A0);
  // Adjust the flame threshold based on your sensor and environment
  if (flameValue > 200) {
    digitalWrite(9, HIGH);
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
    digitalWrite(9, LOW);
    servoMotor.write(0);
  }
}
else{
 pump=false; 
}}