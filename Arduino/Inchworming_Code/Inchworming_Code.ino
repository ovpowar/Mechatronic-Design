#define solenoidVertical1 2
#define solenoidVertical2 4
#define solenoidHorizontal1 6
#define solenoidHorizontal2 7
#define XSpeed 11
#define XCW 12
#define XCCW 13
#define XLength A0
#define trigPin 5
#define echoPin 3
#define ACTUATOR_X_LOWER_LIMIT 50
#define ACTUATOR_X_UPPER_LIMIT 150


#define YSpeed 10
#define YCW 9
#define YCCW 8
#define YLength A1
#define ACTUATOR_Y_LOWER_LIMIT 50
#define ACTUATOR_Y_UPPER_LIMIT 150

long duration;
float xactuator_length;
float yactuator_length;
float cm;
char x;
void setup() {
  // put your setup code here, to run once:
  pinMode(XCW,OUTPUT);
  pinMode(XCCW,OUTPUT);
  pinMode(XSpeed, OUTPUT);
  pinMode(YCW,OUTPUT);
  pinMode(YCCW,OUTPUT);
  pinMode(YSpeed, OUTPUT);
  
  pinMode(solenoidVertical1, OUTPUT);
  pinMode(solenoidVertical2, OUTPUT);
  pinMode(solenoidHorizontal1, OUTPUT);
  pinMode(solenoidHorizontal2, OUTPUT);  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
   Serial.begin (9600);
   digitalWrite(solenoidVertical1,HIGH);
   digitalWrite(solenoidHorizontal1,HIGH);
 
 move_horizontal_center();

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
  xactuator_length = actuator_position_check(XLength);
  yactuator_length = actuator_position_check(YLength);
  
  cm = (duration/2)/29.1;
    Serial.print(cm);
    Serial.print(", ");
    Serial.print(xactuator_length);
    Serial.print(", ");
    Serial.print(yactuator_length);
    Serial.println(", ");
    
    if (Serial.available()>0)
  {
    x = Serial.read();

  }
    if (x == '0')
    {
      analogWrite(XSpeed,0); 
      Serial.print("MOTOR STOPPED");
    }
    else if (x == 'a')
    {
      move_vertical_left(cm);
    }
    else if (x == 's')
    {
      move_vertical_top(cm);
    }
    else if (x == 'd')
    {
      move_vertical_right(cm);
    }
    else if (x == 'w')
    {
      move_vertical_bottom(cm);
    }
    else if (x == 'q')
    {
      while (cm < 4)
      {
        move_vertical_right(cm);
        delay(20);
        move_horizontal_right(cm);
        delay(20);
      }
      analogWrite(XSpeed,0);
    }
    else if (x == 'r')
    {
      
        int flag_vertical_complete = move_vertical_left(cm);
        if (flag_vertical_complete == 1)
        {
          delay(20);
          int flag_horizontal_complete = move_horizontal_left(cm);
          if ( flag_horizontal_complete == 1)
          {
            delay(20);
            analogWrite(XSpeed,0);
          }

        }
    }
    else if (x == 'x')
    {
      Serial.println("*BEWARE!! ROBOT IS FALLING IN 3 SECONDS*");
      delay(3000);
      analogWrite(XSpeed,0);
      digitalWrite(solenoidVertical1,0);       //Beware Robot will fall
      digitalWrite(solenoidVertical2,HIGH);
      digitalWrite(solenoidHorizontal1,0);
      digitalWrite(solenoidHorizontal2,HIGH);
      
      
      xactuator_length = actuator_position_check(XLength);

    }
    
    
    
  
}


int move_vertical_left(int cm)
{
  Serial.println("LOL");
      digitalWrite(solenoidHorizontal1,HIGH);       //Horizontals are fixed
      delay(3000);
      digitalWrite(solenoidHorizontal2,0);
      digitalWrite(solenoidVertical1,0);
      digitalWrite(solenoidVertical2,HIGH);
  while (xactuator_length < ACTUATOR_X_UPPER_LIMIT)
  {
      xactuator_length = actuator_position_check(XLength);
      Serial.println(xactuator_length);
      digitalWrite(XCCW,HIGH);
      digitalWrite(XCW,0);         // Black towards wire
      analogWrite(XSpeed, 255);  
   }
   analogWrite(XSpeed, 0);
   return 1;

}

int move_vertical_top(int cm)
{
  Serial.println("LOL");
      digitalWrite(solenoidHorizontal1,HIGH);       //Horizontals are fixed
      delay(3000);
      digitalWrite(solenoidHorizontal2,0);
      digitalWrite(solenoidVertical1,0);
      digitalWrite(solenoidVertical2,HIGH);
  while (yactuator_length < ACTUATOR_Y_UPPER_LIMIT)
  {
      yactuator_length = actuator_position_check(YLength);
      Serial.println(yactuator_length);
      digitalWrite(YCCW,HIGH);
      digitalWrite(YCW,0);         // Black towards wire
      analogWrite(YSpeed, 255);  
   }
   analogWrite(YSpeed, 0);
   return 1;

}

int move_vertical_bottom(int cm)
{
  Serial.println("LOL");
      digitalWrite(solenoidHorizontal1,HIGH);       //Horizontals are fixed
      delay(3000);
      digitalWrite(solenoidHorizontal2,0);
      digitalWrite(solenoidVertical1,0);
      digitalWrite(solenoidVertical2,HIGH);
  while (yactuator_length > ACTUATOR_Y_LOWER_LIMIT)
  {
      yactuator_length = actuator_position_check(YLength);
      Serial.println(yactuator_length);
      digitalWrite(YCCW,0);
      digitalWrite(YCW,HIGH);         // Black towards wire
      analogWrite(YSpeed, 255);  
   }
   analogWrite(YSpeed, 0);
   return 1;

}



int move_horizontal_left(int cm)
{
       digitalWrite(solenoidVertical1,HIGH);       //Verticals are fixed
      delay(3000);
      digitalWrite(solenoidVertical2,0);
      digitalWrite(solenoidHorizontal1,0);
      digitalWrite(solenoidHorizontal2,HIGH);
   
  if (cm >22 || cm == 0)
  {
    while (xactuator_length > ACTUATOR_X_LOWER_LIMIT)
    {
      xactuator_length = actuator_position_check(XLength);
      Serial.println(xactuator_length);
      digitalWrite(XCCW,0);        //Black away from wire
      digitalWrite(XCW,HIGH);
      analogWrite(XSpeed, 255);
    }
    analogWrite(XSpeed, 0);
    
  }
  else
  {
    float ultrasonic = cm;
    float prev_xactuator_length = actuator_position_check(XLength);
    Serial.print(ultrasonic - 3);
    Serial.print(", ");
    
    Serial.println(prev_xactuator_length);
    
    delay(1000);
    while ((prev_xactuator_length - xactuator_length  < (ultrasonic - 3)) && xactuator_length > 5)
    {
     xactuator_length = actuator_position_check(XLength);
      Serial.println(xactuator_length); 
      digitalWrite(XCCW,0);        //Black away from wire
      digitalWrite(XCW,HIGH);
      analogWrite(XSpeed, 200);
    }
    analogWrite(XSpeed, 0);
  }
  return 1;

}


int move_vertical_right(int cm)
{
      digitalWrite(solenoidHorizontal1,HIGH);       //Horizontals are fixed
      analogWrite(XSpeed,0);
      delay(3000);
      digitalWrite(solenoidHorizontal2,0);
      digitalWrite(solenoidVertical1,0);
      digitalWrite(solenoidVertical2,HIGH);
  while (xactuator_length > ACTUATOR_X_LOWER_LIMIT)
  {
      xactuator_length = actuator_position_check(XLength);
      Serial.println(xactuator_length);
      digitalWrite(XCCW,0);      //Black away from wire
      digitalWrite(XCW,HIGH);
      analogWrite(XSpeed, 255);
  }
     analogWrite(XSpeed, 0);
    return 1;

}


int move_horizontal_right(int cm)
{
        digitalWrite(solenoidVertical1,HIGH);       //Verticals are fixed
        analogWrite(XSpeed,0);
      delay(3000);
      digitalWrite(solenoidVertical2,0);
      digitalWrite(solenoidHorizontal1,0);
      digitalWrite(solenoidHorizontal2,HIGH);
    while (xactuator_length < ACTUATOR_X_UPPER_LIMIT)
    {
     xactuator_length = actuator_position_check(XLength);
     Serial.println(xactuator_length);
     digitalWrite(XCCW,HIGH);
      digitalWrite(XCW,0);       //Black towards wire
      analogWrite(XSpeed, 255);
    }
   analogWrite(XSpeed, 0);
    return 1;
}

float actuator_position_check(int pin)
 {
  int adc_value;
 for (int i=0;i<50;i++)
  {
    adc_value = adc_value+analogRead(pin);
  }

  adc_value = adc_value/50;
  float actuator_position = map(adc_value,0,1024,0,300);
  return actuator_position;
}

float move_horizontal_center()
{
   while(xactuator_length > 150)
 {
  digitalWrite(XCCW,0);
 
 digitalWrite(XCW, HIGH);
 analogWrite(XSpeed, 200);
}
 analogWrite(XSpeed, 0); 

}


