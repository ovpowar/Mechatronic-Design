#include <Servo.h> 

int trigPin = 5;    // Trigger
int echoPin = 3;    // Echo
long duration;  
float cm, inches;
float distance;
int adc_value;
int voltage;
int i;
float angle;
float previous_angle;
Servo myservo;
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(13,OUTPUT);

   myservo.attach(11);

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
  duration = pulseIn(echoPin, HIGH);
 
  
  for (i=0;i<50;i++)
{
adc_value = adc_value+analogRead(A0);
}

adc_value = adc_value/50;

voltage = map(adc_value, 0,1024,0,5);
distance = 9.8011*pow(voltage,4) - 78.095*pow(voltage,3) + 226.32*pow(voltage,2) - 291.11*voltage + 158.5;

angle = map(analogRead(A2),0,1024,0,270);
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135

  Serial.print(cm);
  Serial.print(",");
  Serial.print(angle);
  Serial.print(",");
  Serial.println();

  angle = map(angle,0,270,0,180);
  if (angle-previous_angle > 4 || previous_angle-angle > 4) 
  myservo.write(180 - angle);  // set servo to mid-point
  delay(25);
  previous_angle = angle;
}





