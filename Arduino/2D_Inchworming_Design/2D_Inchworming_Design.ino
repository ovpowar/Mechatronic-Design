#define solenoidVertical1 8
#define solenoidVertical2 9
#define solenoidHorizontal1 6
#define solenoidHorizontal2 7
#define motorSpeed 11
#define motorCW 12
#define motorCCW 13
#define rotaryEncoderPin A0
#define trigPin 5
#define echoPin 3
#define ACTUATOR_X_LOWER_LIMIT 50
#define ACTUATOR_X_UPPER_LIMIT 290

long duration;
float actuator_length;
float cm;
char x;
void setup() {
  // put your setup code here, to run once:
 pinMode(motorCW,OUTPUT);
  pinMode(motorCCW,OUTPUT);
  pinMode(motorSpeed, OUTPUT);
  pinMode(solenoidVertical1, OUTPUT);
  pinMode(solenoidVertical2, OUTPUT);
  pinMode(solenoidHorizontal1, OUTPUT);
  pinMode(solenoidHorizontal2, OUTPUT);  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
   Serial.begin (9600);
   digitalWrite(solenoidVertical1,HIGH);
   digitalWrite(solenoidHorizontal1,HIGH);
 digitalWrite(motorCCW,0);
 digitalWrite(motorCW, HIGH);
 analogWrite(motorSpeed, 200);
 delay(500);
 analogWrite(motorSpeed, 0); 

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
  actuator_length = actuator_position_check();
  cm = (duration/2)/29.1;
    Serial.print(cm);
    Serial.print(", ");
    Serial.print(actuator_length);
    Serial.println(",");
    if (Serial.available()>0)
  {
    x = Serial.read();

  }
    if (x == '0')
    {
      analogWrite(motorSpeed,0); 
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
    else if (x == 'a')
    {
      while (cm < 4)
      {
        move_vertical_right(cm);
        delay(20);
        move_horizontal_right(cm);
        delay(20);
      }
      analogWrite(motorSpeed,0);
    }
    else if (x == 'd')
    {
      
        int flag_vertical_complete = move_vertical_left(cm);
        if (flag_vertical_complete == 1)
        {
          delay(20);
          int flag_horizontal_complete = move_horizontal_left(cm);
          if ( flag_horizontal_complete == 1)
          {
            delay(20);
            analogWrite(motorSpeed,0);
          }

        }
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
      
      
      actuator_length = actuator_position_check();

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
  while (actuator_length < ACTUATOR_X_UPPER_LIMIT)
  {
      actuator_length = actuator_position_check();
      Serial.println(actuator_length);
      digitalWrite(motorCCW,HIGH);
      digitalWrite(motorCW,0);         // Black towards wire
      analogWrite(motorSpeed, 255);  
   }
   analogWrite(motorSpeed, 0);
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
    while (actuator_length > ACTUATOR_X_LOWER_LIMIT)
    {
      actuator_length = actuator_position_check();
      Serial.println(actuator_length);
      digitalWrite(motorCCW,0);        //Black away from wire
      digitalWrite(motorCW,HIGH);
      analogWrite(motorSpeed, 255);
    }
    analogWrite(motorSpeed, 0);
    
  }
  else
  {
    float ultrasonic = cm;
    float prev_actuator_length = actuator_position_check();
    Serial.print(ultrasonic - 3);
    Serial.print(", ");
    
    Serial.println(prev_actuator_length);
    
    delay(1000);
    while ((prev_actuator_length - actuator_length  < (ultrasonic - 3)) && actuator_length > 5)
    {
     actuator_length = actuator_position_check();
      Serial.println(actuator_length); 
      digitalWrite(motorCCW,0);        //Black away from wire
      digitalWrite(motorCW,HIGH);
      analogWrite(motorSpeed, 200);
    }
    analogWrite(motorSpeed, 0);
  }
  return 1;

}


int move_vertical_right(int cm)
{
      digitalWrite(solenoidHorizontal1,HIGH);       //Horizontals are fixed
      analogWrite(motorSpeed,0);
      delay(3000);
      digitalWrite(solenoidHorizontal2,0);
      digitalWrite(solenoidVertical1,0);
      digitalWrite(solenoidVertical2,HIGH);
  while (actuator_length > ACTUATOR_X_LOWER_LIMIT)
  {
      actuator_length = actuator_position_check();
      Serial.println(actuator_length);
      digitalWrite(motorCCW,0);      //Black away from wire
      digitalWrite(motorCW,HIGH);
      analogWrite(motorSpeed, 255);
  }
     analogWrite(motorSpeed, 0);
    return 1;

}


int move_horizontal_right(int cm)
{
        digitalWrite(solenoidVertical1,HIGH);       //Verticals are fixed
        analogWrite(motorSpeed,0);
      delay(3000);
      digitalWrite(solenoidVertical2,0);
      digitalWrite(solenoidHorizontal1,0);
      digitalWrite(solenoidHorizontal2,HIGH);
    while (actuator_length < ACTUATOR_X_UPPER_LIMIT)
    {
     actuator_length = actuator_position_check();
     Serial.println(actuator_length);
     digitalWrite(motorCCW,HIGH);
      digitalWrite(motorCW,0);       //Black towards wire
      analogWrite(motorSpeed, 255);
    }
   analogWrite(motorSpeed, 0);
    return 1;
}

float actuator_position_check()
 {
  int adc_value;
 for (int i=0;i<50;i++)
  {
    adc_value = adc_value+analogRead(rotaryEncoderPin);
  }

  adc_value = adc_value/50;
  float actuator_position = map(adc_value,0,1024,0,300);
  return actuator_position;
}
