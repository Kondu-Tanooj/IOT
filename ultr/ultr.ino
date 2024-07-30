const int trig = A0;
const int echo = A1;
long dur=0;
long dis=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  dur= pulseIn(echo,HIGH);
  dis=dur*0.034/2;
  Serial.println(dis);
  delay(1000);
}
