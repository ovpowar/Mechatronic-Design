#include <Servo.h> 
#include <Stepper.h>


#define solenoidPin1 7
#define solenoidPin2 13
#define trigPin 5
#define echoPin 3
#define servoPin 4
#define motorCW 6
#define motorCCW 8
#define buttonPin 2
#define rotaryEncoderPin A0
#define potentiometerPin A2

long duration;  
float cm, inches;
float distance;
int adc_value;
int voltage;
int i;
float angle_servo, angle_dc;
float previous_angle;
int motor_stat=0;
Servo myservo;
int input;
Stepper myStepper(20, 12,9,10,11);  


int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorCW,OUTPUT);
  pinMode(motorCCW,OUTPUT);
   myservo.attach(servoPin);
  pinMode(solenoidPin1,OUTPUT);
    myStepper.setSpeed(100);

}
 
void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:

  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  pinMode(echoPin, INPUT);
 
  
//  for (i=0;i<50;i++)
//{
//duration = duration+pulseIn(echoPin, HIGH);;
//}
//
//duration = duration/50;

duration = pulseIn(echoPin,HIGH,5000);

angle_servo = map(analogRead(potentiometerPin),0,1024,0,270);
angle_dc = map(analogRead(rotaryEncoderPin),0,1024,0,360);

//  angle_servo= map(angle_servo,0,270,0,180);
//  myservo.write(180 - angle_servo);
//  delay(25);
//  previous_angle = angle_servo;

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  
  Serial.print(cm);
  Serial.print(",");
  Serial.print(angle_servo);
  Serial.print(",");
  Serial.print(angle_dc);
  Serial.print(",");
  Serial.print(motor_stat);
  Serial.print(",");
  //Serial.println();
  
  if(Serial.available()>0)
  {
    char x = Serial.read();
    if (x == '*')
    {
      motor_stat = Serial.parseInt();
    } 
  else
  {
    input = Serial.parseInt();
    
  }
  }
//----------------Sensor Control----------------------//

//--------------DC Motor--------------
if ((motor_stat&1) == 1)
{
  ultrasonic_dc_motor(cm);
}
else if ((motor_stat&1) == 0)
{
    gui_dc_motor(input);
 
}
//----------End of DC Motor-----------

//----------Servo Motor--------------

if ((motor_stat & 2) == 2)
{
 pot_servo_motor(angle_servo);
}
else if ((motor_stat & 2) == 0)
{
    gui_servo_motor(input);
}
//---------End of Servo Motor---------
//-------------Solenoid---------------

if ((motor_stat&4) == 4)
{
  solenoid_trigger_switch();
}
else if ((motor_stat&4) == 0)
{
    gui_solenoid(input);
}

if ((motor_stat&8) == 0)
{
  gui_stepper(input);
}
//---------End of Solenoid-------------
}



void ultrasonic_dc_motor(int cm)
{
    if (cm > 10.00 && cm < 30.00)
  {
    digitalWrite(motorCCW,HIGH);
    digitalWrite(motorCW,LOW);
  }
  else if (cm < 10.00 && cm > 5.00) 
  {
    digitalWrite(motorCCW,LOW);
    digitalWrite(motorCW,LOW);
  }
  else if (cm < 5.00)
  {
    digitalWrite(motorCCW,LOW);
    digitalWrite(motorCW,HIGH);
  }
}


void gui_dc_motor(int motor_1)
{
    if(motor_1 == 11)     //Forward
    {
      analogWrite(motorCCW,0);
      analogWrite(motorCW,255);
    }
    else if(motor_1 == 12)  //Reverse
    {
      analogWrite(motorCW,0);
      analogWrite(motorCCW,255);
    }
    else if(motor_1 == 10)   //Stop
    {
      digitalWrite(motorCCW,0);
      digitalWrite(motorCW,0);
    }
}

void pot_servo_motor(float angle)
{
  angle= map(angle,0,270,0,180);
  myservo.write(180 - angle);
  delay(25);
  previous_angle = angle;
}

void gui_servo_motor(int motor_2)
{
  Serial.print(motor_2);
  Serial.println(",");
  if (motor_2/1000 == 2)
  {
      myservo.write(motor_2%1000);
  }
  
}


void solenoid_trigger_switch()
{
 int reading = digitalRead(buttonPin);
 if (reading != lastButtonState) {
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    buttonState = (~(reading) & 1);
  }
  
  digitalWrite(solenoidPin1, buttonState);
  digitalWrite(solenoidPin2, LOW);
  
  lastButtonState = reading;
}
  


void gui_solenoid(int motor_3)
{
  if (motor_3/10 == 3)
  {
    if (motor_3%10 == 1)
   {
    digitalWrite(solenoidPin1,HIGH);
    digitalWrite(solenoidPin2,LOW);
  }
  
  else if (motor_3%10 == 0)
    {
      digitalWrite(solenoidPin1,LOW);
      digitalWrite(solenoidPin2,HIGH);
    }
  }
}


void gui_stepper(int motor_4)
{
  if ((motor_4/100) == 4)
  {
    if ((motor_4%100) >= 50)
  {
      myStepper.step((motor_4%100)-50);
  }
  else if ((motor_4%100) < 50)
  {
    myStepper.step(-(motor_4%100));
  }
  }
  
}

