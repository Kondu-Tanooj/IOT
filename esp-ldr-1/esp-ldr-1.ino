const int ldr = A0;
const int led = D4;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ldr,INPUT);
  pinMode(led,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int ldrdata = analogRead(ldr);
  Serial.println(ldrdata);
  if(ldrdata<150){
    digitalWrite(led,HIGH);
  }
  else{
    digitalWrite(led,LOW);
  }
  delay(1000);
}
