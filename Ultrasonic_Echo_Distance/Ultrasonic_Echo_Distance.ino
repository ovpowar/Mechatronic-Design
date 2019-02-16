  
// defines arduino pins numbers
const int trigPin = 3;
const int echoPin = 5;
long duration;
int distance_in_cm;
int distance_in_inch;

void setup() 
{
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}
void loop() {

trigger();
// Reads the echoPin and checks when it goes from high to low, returns the sound travel time in microseconds
distance_in_cm = duration*0.034/2;  //distance_in_cm Calculation
distance_in_inch  = (duration/2) / 74;  //distance_in_inch Calculation
Serial.println(duration);
  
  Serial.print(distance_in_inch);
  Serial.print(" in, ");
  Serial.print(distance_in_cm);
  Serial.print(" cm");
  Serial.println();
  
  delay(250);
}


void trigger()
{
  digitalWrite(trigPin, LOW);
delayMicroseconds(5);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
}


