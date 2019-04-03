#define solenoidVertical1 3
#define solenoidHorizontal1 4
#define actuatorXSpeed 11
#define actuatorXCW 12
#define actuatorXCCW 13

#define actuatorYSpeed 10
#define actuatorYCW 9
#define actuatorYCCW 8

#define motorZSpeed 5
#define motorZCW 6
#define motorZCCW 7

#define actuatorXpos A0
#define actuatorYpos A1
#define motorZ1Pos A2
#define motorZ2Pos A3

#define trigPin 2
#define echoPin 1
#define ACTUATOR_X_LOWER_LIMIT 50
#define ACTUATOR_X_UPPER_LIMIT 150
#define ACTUATOR_Y_LOWER_LIMIT 50
#define ACTUATOR_Y_UPPER_LIMIT 200

long duration;
float actuatorX_length;
float actuatorY_length;
char zPos;
float cm;
char x;
void setup() {
  // put your setup code here, to run once:
 pinMode(actuatorXCW,OUTPUT);
  pinMode(actuatorXCCW,OUTPUT);
  pinMode(actuatorXSpeed, OUTPUT);
  pinMode(solenoidVertical1, OUTPUT);
  pinMode(solenoidHorizontal1, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(actuatorYCW,OUTPUT);
  pinMode(actuatorYCCW,OUTPUT);
  pinMode(actuatorYSpeed, OUTPUT);
  pinMode(motorZCW,OUTPUT);
  pinMode(motorZCCW,OUTPUT);
  pinMode(motorZSpeed, OUTPUT);
  
   Serial.begin (9600);
   digitalWrite(solenoidVertical1,HIGH);
   digitalWrite(solenoidHorizontal1,HIGH);
 digitalWrite(actuatorXCCW,0);
 digitalWrite(actuatorXCW, HIGH);
 analogWrite(actuatorXSpeed, 200);
 delay(500);
 analogWrite(actuatorXSpeed, 0); 
zPos = 'u';
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH,5000);
  actuatorX_length = actuator_position_check(actuatorXpos);
  actuatorY_length = actuator_position_check(actuatorYpos);
  
//  cm = (duration/2)/29.1;
    cm = 25;
    Serial.print(actuatorX_length);
    Serial.print(", ");
    Serial.print(actuatorY_length);
    Serial.print(",");
    Serial.println(zPos);
    if (Serial.available()>0)
  {
    x = Serial.read();
    
  }
  Serial.println(x);
  
    if (x == '0')
    {
      analogWrite(actuatorXSpeed,0);
      analogWrite(actuatorYSpeed,0);
      analogWrite(motorZSpeed,0);
       
      Serial.print("MOTOR STOPPED");
    }
    else if (x == '1')
    {
      move_vertical_left(cm);
    }
    else if (x == '2')
    {
      move_horizontal_left(cm);
    }
    else if (x == '3')
    {
      move_vertical_right(cm);
    }
    else if (x == '4')
    {
      move_horizontal_right(cm);
    }
    else if (x == '5')
    {
      move_horizontal_bottom(cm);
    }
    else if (x == '6')
    {
      move_vertical_bottom(cm);
    }
    else if (x == '7')
    {
      move_horizontal_top(cm);
    }
    else if (x == '8')
    {
      move_vertical_top(cm);
    }
    else if (x == '9')
    {
      drive_z_up();
      
    }
    else if (x  == '-')
    {
      drive_z_down();
      
    }
    else if (x == 'v')
    {
      stick_vertical_suction();
    }
    else if (x == 'h')
    {
      stick_horizontal_suction();
    }
    else if (x == 't')
    {
      stick_all_suction();
    }
    else if (x == 'a')
    {
        if(move_vertical_left(cm)==1)
        {
          delay(20);
          while(move_horizontal_left(cm)!=1);
          delay(10);
          
        }
    analogWrite(actuatorXSpeed,0);
    }
      
//      while (cm < 4)
//      {
//        move_vertical_right(cm);
//        delay(20);
//        move_horizontal_right(cm);
//        delay(20);
//      }
//      analogWrite(actuatorXSpeed,0);
//    }
    else if (x == 'd')
    {
        if(move_vertical_right(cm)==1)
        {
          delay(20);
          while(move_horizontal_right(cm)!=1);
          delay(10);
        }
    analogWrite(actuatorXSpeed,0);
    }

    else if (x == 's')
    {
        if(move_vertical_bottom(16)==1)
        {
          delay(20);
          while(move_horizontal_bottom(16)!=1);
          delay(10);
        }
    analogWrite(actuatorYSpeed,0);
    }

    
    else if (x == 'x')
    {
      Serial.println("*BEWARE!! ROBOT IS FALLING IN 3 SECONDS*");
      delay(3000);
      analogWrite(actuatorXSpeed,0);
      digitalWrite(solenoidVertical1,0);       //Beware Robot will fall
      digitalWrite(solenoidHorizontal1,0);
      
      
      actuatorX_length = actuator_position_check(actuatorXpos);

    }
    
    
    
  
}


int move_vertical_left(int cm)
{
  Serial.println("VL");
if (zPos!='d')
{
      drive_z_down();
      stick_all_suction();
      drive_z_down_test(1000);
      stick_horizontal_suction();            
      drive_z_down();
      zPos = 'd';  
}
analogWrite(actuatorXSpeed,0);
  while (actuatorX_length < ACTUATOR_X_UPPER_LIMIT)
  {
      actuatorX_length = actuator_position_check(actuatorXpos);
      Serial.println(actuatorX_length);
      digitalWrite(actuatorXCCW,HIGH);
      digitalWrite(actuatorXCW,0);         // Black towards wire
      analogWrite(actuatorXSpeed, 255);  
   }
   analogWrite(actuatorXSpeed, 0);
   return 1;

}
int move_horizontal_left(int cm)
{
       Serial.println("HL"); 
       if (zPos!='u')
       {
       drive_z_up();
       stick_all_suction();
        drive_z_up_test(1000);
        stick_vertical_suction();
        drive_z_up();       
       zPos = 'u';        
       }
  if (cm >15 || cm == 0)
  {
    while (actuatorX_length > ACTUATOR_X_LOWER_LIMIT)
    {
      actuatorX_length = actuator_position_check(actuatorXpos);
      Serial.println(actuatorX_length);
      digitalWrite(actuatorXCCW,0);        //Black away from wire
      digitalWrite(actuatorXCW,HIGH);
      analogWrite(actuatorXSpeed, 255);
    }
    analogWrite(actuatorXSpeed, 0);
  }
  else
  {
    float ultrasonic = cm;
    float prev_actuatorX_length = actuator_position_check(actuatorXpos);
    Serial.print(ultrasonic - 3);
    Serial.print(", ");
    
    Serial.println(prev_actuatorX_length);
    
    delay(1000);
    while ((prev_actuatorX_length - actuatorX_length  < (ultrasonic - 3)) && actuatorX_length > 5)
    {
     actuatorX_length = actuator_position_check(actuatorXpos);
      Serial.println(actuatorX_length); 
      digitalWrite(actuatorXCCW,0);        //Black away from wire
      digitalWrite(actuatorXCW,HIGH);
      analogWrite(actuatorXSpeed, 200);
    }
    analogWrite(actuatorXSpeed, 0);
  }
  return 1;

}


int move_vertical_right(int cm)
{
      Serial.println("VR");
if (zPos!='d')
{
      drive_z_down();
      stick_all_suction();
      drive_z_down_test(1000);
      stick_horizontal_suction();            
      drive_z_down();
      zPos = 'd';  
}
      analogWrite(actuatorXSpeed,0);
      
  while (actuatorX_length > ACTUATOR_X_LOWER_LIMIT)
  {
      actuatorX_length = actuator_position_check(actuatorXpos);
      Serial.println(actuatorX_length);
      digitalWrite(actuatorXCCW,0);      //Black away from wire
      digitalWrite(actuatorXCW,HIGH);
      analogWrite(actuatorXSpeed, 255);
  }
     analogWrite(actuatorXSpeed, 0);
    return 1;

}


int move_horizontal_right(int cm)
{
  Serial.println("HR");
       if (zPos!='u')
       {
       drive_z_up();
       stick_all_suction();
        drive_z_up_test(1000);
        stick_vertical_suction();
        drive_z_up();       
       zPos = 'u';        
       }
      
    while (actuatorX_length < ACTUATOR_X_UPPER_LIMIT)
    {
     actuatorX_length = actuator_position_check(actuatorXpos);
     Serial.println(actuatorX_length);
     digitalWrite(actuatorXCCW,HIGH);
      digitalWrite(actuatorXCW,0);       //Black towards wire
      analogWrite(actuatorXSpeed, 255);
    }
   analogWrite(actuatorXSpeed, 0);
    return 1;
}


int move_vertical_bottom(int cm)
{
      Serial.println("VB");
  if (zPos != 'd')
  {
      drive_z_down();
      stick_all_suction();
      drive_z_down_test(1000);
      stick_horizontal_suction();      
      drive_z_down();    
  }
      zPos = 'd';
      analogWrite(actuatorYSpeed,0);
      delay(2000);
      digitalWrite(solenoidVertical1,0);
      
  while (actuatorY_length < ACTUATOR_Y_UPPER_LIMIT)
  {
      actuatorY_length = actuator_position_check(actuatorYpos);
      Serial.println(actuatorY_length);
      digitalWrite(actuatorYCCW,HIGH);      //Black towards wire
      digitalWrite(actuatorYCW,0);
      analogWrite(actuatorYSpeed, 255);
  }
     analogWrite(actuatorYSpeed, 0);
    return 1;

}

int move_horizontal_bottom(int cm)
{
      Serial.println("HB");
  if (zPos != 'u')
  {
      drive_z_up();
      stick_all_suction();
      drive_z_up_test(1000);
      stick_vertical_suction();      
      drive_z_up();    
  }
      zPos = 'u';
      analogWrite(actuatorYSpeed,0);
      delay(2000);
      
  while (actuatorY_length > ACTUATOR_Y_LOWER_LIMIT)
  {
      actuatorY_length = actuator_position_check(actuatorYpos);
      Serial.println(actuatorY_length);
      digitalWrite(actuatorYCCW,0);      //Black away from wire
      digitalWrite(actuatorYCW,HIGH);
      analogWrite(actuatorYSpeed, 255);
  }
     analogWrite(actuatorYSpeed, 0);
    return 1;

}


int move_horizontal_top(int cm)
{
  Serial.println("HT");
  if (zPos != 'u')
  {
      drive_z_up();
      stick_all_suction();
      drive_z_up_test(1000);
      stick_vertical_suction();      
      drive_z_up();    
  }
      zPos = 'u';
      analogWrite(actuatorYSpeed,0);
      
  while (actuatorY_length < ACTUATOR_Y_UPPER_LIMIT)
  {
      actuatorY_length = actuator_position_check(actuatorYpos);
      Serial.println(actuatorY_length);
      digitalWrite(actuatorYCCW,HIGH);      //Black away from wire
      digitalWrite(actuatorYCW,0);
      analogWrite(actuatorYSpeed, 255);
  }
     analogWrite(actuatorYSpeed, 0);
    return 1;
}

int move_vertical_top(int cm)
{
      Serial.println("VT");
  if (zPos != 'd')
  {
      drive_z_down();
      stick_all_suction();
      drive_z_down_test(1000);
      stick_horizontal_suction();      
      drive_z_down();    
  }

      zPos = 'd';
      analogWrite(actuatorYSpeed,0);
      
  while (actuatorY_length > ACTUATOR_Y_LOWER_LIMIT)
  {
      actuatorY_length = actuator_position_check(actuatorYpos);
      Serial.println(actuatorY_length);
      digitalWrite(actuatorYCCW,0);      //Black towards wire
      digitalWrite(actuatorYCW,HIGH);
      analogWrite(actuatorYSpeed, 255);
  }
     analogWrite(actuatorYSpeed, 0);
    return 1;
  
}
float actuator_position_check(int Pin)
 {
  int adc_value;
 for (int i=0;i<50;i++)
  {
    adc_value = adc_value+analogRead(Pin);
  }

  adc_value = adc_value/50;
  float actuator_position = map(adc_value,0,1024,0,300);
  return actuator_position;
}

void stick_all_solenoids()
{
  digitalWrite(solenoidHorizontal1,HIGH);
  digitalWrite(solenoidVertical1,HIGH);
  delay(5000);  
}


void drive_z_down()
{
  Serial.println("BITCH");
  digitalWrite(motorZCW,HIGH);
  digitalWrite(motorZCCW,0);
  analogWrite(motorZSpeed,150);
  delay(3000);
  analogWrite(motorZSpeed,0);    
//  }
//  else
//  {
//  analogWrite(motorZSpeed,0);      
//  Serial.println("It is already down!");
//  delay(2500);
//  }
}

void drive_z_down_test(int time_to_push)
{
  Serial.println("HENLO");
  digitalWrite(motorZCW,HIGH);
  digitalWrite(motorZCCW,0);
  analogWrite(motorZSpeed,150);
  delay(time_to_push);
  analogWrite(motorZSpeed,0);    
//  }
//  else
//  {
// analogWrite(motorZSpeed,0);      
//  Serial.println("It is already up!");
//  delay(2500);
//  }
}

void drive_z_up()
{
  Serial.println("HENLO");
  digitalWrite(motorZCW,0);
  digitalWrite(motorZCCW,HIGH);
  analogWrite(motorZSpeed,150);
  delay(3000);
  analogWrite(motorZSpeed,0);    
//  }
//  else
//  {
// analogWrite(motorZSpeed,0);      
//  Serial.println("It is already up!");
//  delay(2500);
//  }
}

void drive_z_up_test(int time_to_push)
{
  Serial.println("HENLO");
  digitalWrite(motorZCW,0);
  digitalWrite(motorZCCW,HIGH);
  analogWrite(motorZSpeed,150);
  delay(time_to_push);
  analogWrite(motorZSpeed,0);    
//  }
//  else
//  {
// analogWrite(motorZSpeed,0);      
//  Serial.println("It is already up!");
//  delay(2500);
//  }
}


void stick_vertical_suction()
{
  Serial.println("YAY");
  digitalWrite(solenoidVertical1,HIGH);
  digitalWrite(solenoidHorizontal1,0);
  delay(2000);
}

void stick_horizontal_suction()
{
  digitalWrite(solenoidHorizontal1,HIGH);
  digitalWrite(solenoidVertical1,0);
  delay(2000);
  
}

void stick_all_suction()
{
  digitalWrite(solenoidHorizontal1,HIGH);
  digitalWrite(solenoidVertical1,HIGH);
  delay(2000);
  
}


