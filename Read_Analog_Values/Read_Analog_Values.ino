void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}
int distance;
int adc_value;
int voltage;
int i;
void loop() {
  // put your main code here, to run repeatedly:
for (i=0;i<50;i++)
{
adc_value = adc_value+analogRead(A0);
}

adc_value = adc_value/50;

voltage = map(adc_value, 0,1024,0,5);
distance = 9.8011*pow(voltage,4) - 78.095*pow(voltage,3) + 226.32*pow(voltage,2) - 291.11*voltage + 158.5;
Serial.print(distance);
Serial.println(" cm");
Serial.println(adc_value);

delay(1000);
}
