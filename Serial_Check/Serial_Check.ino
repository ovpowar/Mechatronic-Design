void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(A0,INPUT);
pinMode(A2, INPUT);
pinMode(2,OUTPUT);

}
float a,b,x;

void loop() {
  // put your main code here, to run repeatedly:

a=analogRead(A0);
Serial.print(a);
Serial.print(",");
b=analogRead(A2);
Serial.print(b);
Serial.print(",");


//Serial.println();
while(Serial.available())
{
 
  digitalWrite(7,LOW);
  Serial.println("HI");
}

delay(100);
}
