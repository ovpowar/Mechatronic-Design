#define motorCW 6
#define motorCCW 8
#define rotaryEncoderPin A0


//#define left 3
//#define right 4
//#define horizontal_actuator_positive 9
//#define horizontal_actuator_negative 10
//#define horizontal_actuator_speed 11
//#define ultrasonic_sensor_trig 3
//#define ultrasonic_sensor_echo 5
#define rotary_encoder A0 
//#define time_based_on HIGH
float angle_dc;

void setup() {
  // put your setup code here, to run once:
 pinMode(motorCW,OUTPUT);
  pinMode(motorCCW,OUTPUT);
   Serial.begin (9600);
   

}

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
}

void motor_stop(void)
{
    digitalWrite(motorCCW,0);
      digitalWrite(motorCW,0);

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

