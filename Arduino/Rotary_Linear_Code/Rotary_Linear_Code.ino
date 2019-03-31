#define motorCW 12
#define motorCCW 13
#define motorSpeed 11
#define rotaryEncoderPin A0


//#define motorCW 8
//#define motorCCW 9
//#define motorSpeed 10
//#define rotaryEncoderPin A1

float angle_dc;
void setup() {
  // put your setup code here, to run once:
 pinMode(motorCW,OUTPUT);
  pinMode(motorCCW,OUTPUT);
  pinMode(motorSpeed, OUTPUT);
   Serial.begin (9600);


}

void loop() {
  // put your main code here, to run repeatedly:
angle_dc = map(analogRead(rotaryEncoderPin),0,1024,0,300);
digitalWrite(motorSpeed, HIGH);
 Serial.print(angle_dc);
  Serial.println(",");

  if (Serial.available()>0)
  {
    char x = Serial.read();
  
  
    if (x == '0')
    {
      digitalWrite(motorCCW,0);
      digitalWrite(motorCW,0);
      angle_dc = map(analogRead(rotaryEncoderPin),0,1024,0,25);

    }
    else if (x == '1')
    {
        digitalWrite(motorCCW,0);
        digitalWrite(motorCW,HIGH);
        angle_dc = map(analogRead(rotaryEncoderPin),0,1024,0,25);
      Serial.println(angle_dc);
      //digitalWrite(motorCCW,0);
      //digitalWrite(motorCW,0);
    
    }
    else if (x == '2')
    {
        digitalWrite(motorCCW,HIGH);
        digitalWrite(motorCW,0);
        angle_dc = map(analogRead(rotaryEncoderPin),0,1024,0,25);
        Serial.println(angle_dc);

//      digitalWrite(motorCCW,0);
//      digitalWrite(motorCW,0);
    
    }
  
   }

}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char x = Serial.read();
    if (x == '0')
    {
      digitalWrite(motorCW,0);
      digitalWrite(motorCCW,0);
    }
    
  }
}
