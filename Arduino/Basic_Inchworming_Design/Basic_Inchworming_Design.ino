

#define solenoidVertical1 3
#define solenoidVertical2 2
#define solenoidHorizontal1 4
#define solenoidHorizontal2 1
//#define motorSpeed 5    //1 Sends Cups Down
//#define motorCW 6       //2 Sends Cups Up
//#define motorCCW 7


//X Actuator
//#define motorSpeed 11     //1 sends it Towards Black
//#define motorCW 12        //2 sends it Away from Black
//#define motorCCW 13

//Y Actuator
#define motorSpeed 10     //1 sends it Towards Black
#define motorCW 9        //2 sends it Away from Black
#define motorCCW 8
#define rotaryEncoderPin A1


//#define ultrasonic_sensor_trig 3
//#define ultrasonic_sensor_echo 5
//#define time_based_on HIGH
float angle_dc;

void setup() {
  // put your setup code here, to run once:
 pinMode(motorCW,OUTPUT);
  pinMode(motorCCW,OUTPUT);
  pinMode(motorSpeed, OUTPUT);
  pinMode(solenoidVertical1, OUTPUT);
  pinMode(solenoidVertical2, OUTPUT);
  pinMode(solenoidHorizontal1, OUTPUT);
  pinMode(solenoidHorizontal2, OUTPUT);  
   Serial.begin (9600);
   digitalWrite(solenoidVertical1,HIGH);
   digitalWrite(solenoidHorizontal1,HIGH);

}

void loop() {
    if (Serial.available()>0)
  {
    char x = Serial.read();
  
  
    if (x == '0')
    {
      analogWrite(motorSpeed,0);
      
      
      angle_dc = map(analogRead(rotaryEncoderPin),0,1024,0,25);

    }
    else if (x == '1')
    {
      digitalWrite(solenoidHorizontal1,HIGH);       //Horizontals are fixed
      analogWrite(motorSpeed,0);
      delay(3000);
      digitalWrite(solenoidHorizontal2,0);
      digitalWrite(solenoidVertical1,0);
      digitalWrite(solenoidVertical2,HIGH);
        angle_dc = map(analogRead(rotaryEncoderPin),0,1024,0,25);
      Serial.println(angle_dc);
      digitalWrite(motorCCW,0);
      digitalWrite(motorCW,HIGH);
      analogWrite(motorSpeed, 255);
      delay(500);
    }
    else if (x == '2')
    {
      digitalWrite(solenoidVertical1,HIGH);       //Verticals are fixed
      analogWrite(motorSpeed,0);
      delay(3000);
      digitalWrite(solenoidVertical2,0);
      digitalWrite(solenoidHorizontal1,0);
      digitalWrite(solenoidHorizontal2,HIGH);
      digitalWrite(motorCCW,HIGH);
      digitalWrite(motorCW,0);
      analogWrite(motorSpeed, 255);
      delay(500);

        angle_dc = map(analogRead(rotaryEncoderPin),0,1024,0,25);
        Serial.println(angle_dc);

//      digitalWrite(motorCCW,0);
//      digitalWrite(motorCW,0);
    
    }
    else if (x == 'x')
    {
      Serial.println("*BEWARE!! ROBOT IS FALLING IN 3 SECONDS*");
      delay(3000);
      analogWrite(motorSpeed,0);
      digitalWrite(solenoidVertical1,0);       //Beware Robot will fall
      digitalWrite(solenoidVertical2,HIGH);
      digitalWrite(solenoidHorizontal1,0);
      digitalWrite(solenoidHorizontal2,HIGH);
      
      
      angle_dc = map(analogRead(rotaryEncoderPin),0,1024,0,25);

    }
    
    
    
  
   }
}

/*
void loop() {
  angle_dc = map(analogRead(rotaryEncoderPin),0,1024,0,25);

  motor_stop();
  Serial.print(angle_dc);
  Serial.println(",");

  if (Serial.available()>0)
  {
    char x = Serial.read();
  
  
    if (x == '0')
    {
     angle_dc = map(analogRead(rotaryEncoderPin),0,1024,0,25);
     
    }
    if (x == '1')
    {
      while (angle_dc > 2)
      {
        move_left();
        angle_dc = map(analogRead(rotaryEncoderPin),0,1024,0,25);
        Serial.println(angle_dc);
        if (Serial.read() == '0')
        {
          motor_stop();
        }
      }
      motor_stop();
    }
    if (x == '2')
    {
      while (angle_dc < 25)
      {
        move_right();
        angle_dc = map(analogRead(rotaryEncoderPin),0,1024,0,25);
        Serial.println(angle_dc);
        if (Serial.read() == '0')
        {
          motor_stop();
        }
      }
      
      motor_stop();
      while (angle_dc > 2)
      {
        move_left();
        angle_dc = map(analogRead(rotaryEncoderPin),0,1024,0,25);
        Serial.println(angle_dc);
        if (Serial.read() == '0')
        {
          motor_stop();
        }
      }
      
    }
  }   
}

/// Take the step to Right

void move_right(void)
{
  // put your main code here, to run repeatedly:
        digitalWrite(motorCCW,LOW);
        digitalWrite(motorCW,HIGH);
}

void move_left(void)
{
  // put your main code here, to run repeatedly:
        digitalWrite(motorCCW,HIGH);
        digitalWrite(motorCW,LOW);
        analogWrite(motorSpeed, 125);
        digitalWrite(solenoidVertical1, HIGH);
        digitalWrite(solenoidVertical2, LOW);
        
}

void motor_stop(void)
{
    digitalWrite(motorCCW,0);
      digitalWrite(motorCW,0);
    digitalWrite(solenoidVertical1, LOW);
    digitalWrite(solenoidVertical2, HIGH);
    
}

//vacuum_position(left,LOW);
//drive(horizontal_actuator_positive,time_based_on);
//vacuum_position(left,HIGH);
//delay(1000);  //Depends on how much time is needed to create vacuum
//vacuum_position(right,LOW);
//drive(horizontal_actuator_negative,time_based_on);
//vacuum_position(right,HIGH);
//}
//
//void vacuum_position(int vacuum_side, bool vacuum_status)
//{
//  digitalWrite(vacuum_side, vacuum_status);
//  Serial.print(vacuum_side);
//  Serial.print(" ");
//  Serial.println(vacuum_status);
//}
//
//
//void drive(int driver_pin, bool time_based)
//{
//  if (time_based==HIGH)
//  {
//    digitalWrite(driver_pin, HIGH);
//    delay(5000);
//    digitalWrite(driver_pin, LOW);
//  }
//  else
//  {
//    
//  }
//}
*/

