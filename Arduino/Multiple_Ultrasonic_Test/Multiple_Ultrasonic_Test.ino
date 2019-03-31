
int trigPin = 3;    // Trigger
int echoPinLeft = 7;    // Echo 1
int echoPinRight = 4;    // Echo 2 
int echoPinTop = 5;
int echoPinBottom = 6;
long duration_left, duration_right, duration_top, duration_bottom;  
float cm_left, inches_left; 
float cm_right,inches_right;
float cm_top,inches_top;
float cm_bottom,inches_bottom;

float distance;
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPinLeft, INPUT);
  pinMode(echoPinRight, INPUT);
  pinMode(echoPinTop, INPUT);
  pinMode(echoPinBottom, INPUT);
  
  pinMode(13,OUTPUT);

}
 char selectUS;
 
void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    pinMode(echoPinLeft, INPUT);
    duration_left = pulseIn(echoPinLeft, HIGH);    
    delay(5);
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    pinMode(echoPinRight, INPUT);
    duration_right = pulseIn(echoPinRight, HIGH);    
    delay(5);
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    pinMode(echoPinTop, INPUT);
    duration_top = pulseIn(echoPinTop, HIGH);    
    delay(5);
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    pinMode(echoPinBottom, INPUT);
    duration_bottom = pulseIn(echoPinBottom, HIGH);    

  if (Serial.available()>0)
  {
    selectUS = Serial.read();
  }
  Serial.println(selectUS);
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  
  // Convert the time into a distance
  cm_left = (duration_left/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches_left = (duration_left/2) / 74;   // Divide by 74 or multiply by 0.0135
  cm_right = (duration_right/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches_right = (duration_right/2) / 74;   // Divide by 74 or multiply by 0.0135
  cm_bottom = (duration_bottom/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches_bottom = (duration_bottom/2) / 74;   // Divide by 74 or multiply by 0.0135
  cm_top = (duration_top/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches_top = (duration_top/2) / 74;   // Divide by 74 or multiply by 0.0135

  Serial.print(cm_top/2.54);
  Serial.print("\t");
  Serial.print(cm_right/2.54);
  Serial.print("\t");
  Serial.print(cm_bottom/2.54);
  Serial.print("\t");
  Serial.print(cm_left/2.54);  
  Serial.println();
delay(500);
}





