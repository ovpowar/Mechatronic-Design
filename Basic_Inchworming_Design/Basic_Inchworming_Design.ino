#define left 3
#define right 4
#define horizontal_actuator_positive 9
#define horizontal_actuator_negative 10
#define time_based_on HIGH
void vacuum_position(int vacuum_side, bool vacuum_status);

void setup() {
  // put your setup code here, to run once:
pinMode(left,OUTPUT);
pinMode(right,OUTPUT);
Serial.begin(9600);
}

void loop() {
  move_right(); 
}


void move_right(void)
{
  // put your main code here, to run repeatedly:
vacuum_position(left, HIGH);
vacuum_position(right, HIGH);
delay(5000);
/// Take the step to Right

vacuum_position(left,LOW);
drive(horizontal_actuator_positive,time_based_on);
vacuum_position(left,HIGH);
delay(1000);  //Depends on how much time is needed to create vacuum
vacuum_position(right,LOW);
drive(horizontal_actuator_negative,time_based_on);
vacuum_position(right,HIGH);
}

void vacuum_position(int vacuum_side, bool vacuum_status)
{
  digitalWrite(vacuum_side, vacuum_status);
  Serial.print(vacuum_side);
  Serial.print(" ");
  Serial.println(vacuum_status);
}


void drive(int driver_pin, bool time_based)
{
  if (time_based==HIGH)
  {
    digitalWrite(driver_pin, HIGH);
    delay(5000);
    digitalWrite(driver_pin, LOW);
  }
  else
  {
    //Need to Code
  }
}

