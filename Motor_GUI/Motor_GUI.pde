import controlP5.*;
import processing.serial.*;


Serial myPort;  // Create object from Serial class

ControlP5 cp5;
ControlP5 cp6;
ControlP5 cp7;
ControlP5 cp8;
ControlP5 cp9;
ControlP5 cp12;

Textlabel myTextlabelA;

Chart Sensor1_Chart;
Chart Sensor2_Chart;
Chart Sensor3_Chart;

CheckBox checkbox;

int lf = 10;
String myString = null;

int sliderValue = 100;
float motor_speed;
int final_setting=0;
void setup() {
  size(1200, 600);
  cp5 = new ControlP5(this);
  cp6 = new ControlP5(this);
  cp7 = new ControlP5(this);
  cp8 = new ControlP5(this);
  cp9 = new ControlP5(this);
  cp12 = new ControlP5(this);
  
  myTextlabelA = cp12.addTextlabel("label")
                    .setText("Vacoomba- Team C")
                    .setPosition(50,20)
                    .setColorValue(0xffffffff)
                    .setFont(createFont("Georgia",20))
                    ;
  
  Sensor1_Chart = cp5.addChart("Ultrasonic Sensor")
               .setPosition(50, 50)
               .setSize(200, 100)
               .setRange(0, 50)
               .setView(Chart.LINE) // use Chart.LINE, Chart.PIE, Chart.AREA, Chart.BAR_CENTERED
               .setStrokeWeight(1.5)
               .setColorCaptionLabel(color(40))
               ;

  Sensor1_Chart.addDataSet("incoming");
  Sensor1_Chart.setData("incoming", new float[100]);

  Sensor2_Chart = cp6.addChart("Potentiometer")
               .setPosition(300, 50)
               .setSize(200, 100)
               .setRange(0, 500)
               .setView(Chart.LINE) // use Chart.LINE, Chart.PIE, Chart.AREA, Chart.BAR_CENTERED
               .setStrokeWeight(1.5)
               .setColorCaptionLabel(color(40))
               ;

  Sensor2_Chart.addDataSet("incoming");
  Sensor2_Chart.setData("incoming", new float[100]);
  
  Sensor3_Chart = cp7.addChart("Rotary Encoder")
               .setPosition(550, 50)
               .setSize(200, 100)
               .setRange(0, 500)
               .setView(Chart.LINE) // use Chart.LINE, Chart.PIE, Chart.AREA, Chart.BAR_CENTERED
               .setStrokeWeight(1.5)
               .setColorCaptionLabel(color(40))
               ;

  Sensor3_Chart.addDataSet("incoming");
  Sensor3_Chart.setData("incoming", new float[100]);
  
  
   cp8.addButton("Motor_1_CW")
     .setValue(0)
     .setPosition(50,250)
     .setSize(200,20)  
     ;
  
   cp8.addButton("Motor_1_CCW")
     .setValue(1)
     .setPosition(50,300)
     .setSize(200,20)  
     ;
  
   cp8.addButton("Motor_1_Stop")
     .setValue(1)
     .setPosition(50,275)
     .setSize(200,20)  
     ;

  
   cp8.addButton("Solenoid_ON")
     .setValue(1)
     .setPosition(50,350)
     .setSize(200,20)  
     ;
       
   cp8.addButton("Solenoid_OFF")
     .setValue(1)
     .setPosition(300,350)
     .setSize(200,20)  
     ;
  cp9.addSlider("Servo")
     .setPosition(300,250)
     .setSize(180,30)
     .setRange(0,180)
     .setValue(90)
     .setSliderMode(Slider.FLEXIBLE)
     ;  
  
  cp9.addSlider("Stepper")
     .setPosition(550,250)
     .setSize(200,30)
     .setRange(0,100)
     .setValue(50)
     .setSliderMode(Slider.FLEXIBLE)  
     ;
  
  
  checkbox = cp12.addCheckBox("checkBox")
                .setPosition(1000, 50)
                .setSize(40, 40)
                .setItemsPerRow(1)
                .setSpacingColumn(30)
                .setSpacingRow(20)
                .addItem("DC Motor", 1)
                .addItem("Servo Motor", 2)
                .addItem("Solenoid", 4)
                .addItem("Stepper", 8)
                ;
  
  printArray(Serial.list());
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[0], 9600); //<>//
 
  myPort.clear();
  // Throw out the first reading, in case we started reading 
  // in the middle of a string from the sender.
  myString = myPort.readStringUntil(lf);
  myString = null;
  delay(2000);
 
}

void draw() {
  
 delay(200);
  background(200);
    while (myPort.available() > 0) {
    myString = myPort.readStringUntil(lf);
    if (myString != null) {
     // println(myString);
    }

  }
  float val[] = float(split(myString, ","));
  
  Sensor1_Chart.push("incoming", (val[0]));
 
  Sensor2_Chart.push("incoming", (val[1]));
  
  Sensor3_Chart.push("incoming", (val[2]));
}


public void Motor_1_CW(int theValue) {
   myPort.write('1');
   myPort.write('1');
   myPort.write('1');
   println(theValue);
   
}

public void Motor_1_CCW(int theValue) {
  myPort.write("112");
   println(theValue);
}

public void Motor_1_Stop(int theValue) {
  myPort.write("110");
   println(theValue);  
}


public void Solenoid_ON(int theValue) {
  myPort.write("331");
   println(theValue);  
}

public void Solenoid_OFF(int theValue) {
  myPort.write("330");
   println(theValue);  
}

void Servo(int motor_speed) {
  println(motor_speed);
  myPort.write("22" + nf(motor_speed,3));
  println("22" + nf(motor_speed,3));
}

void Stepper(int motor_steps) {
  println(motor_steps);
  myPort.write("44" + motor_steps);
  println("44" + motor_steps);
}



void controlEvent(ControlEvent theEvent) {
  if (theEvent.isFrom(checkbox)) {
    final_setting = 0;
    // checkbox uses arrayValue to store the state of 
    // individual checkbox-items. usage:
    println(checkbox.getArrayValue());
    int col = 0;
    for (int i=0;i<checkbox.getArrayValue().length;i++) {
      int n = (int)checkbox.getArrayValue()[i];
      print(n);
      if(n==1) {
        final_setting += checkbox.getItem(i).internalValue();
      }
    }
    println();
    println("*"+final_setting);    
      myPort.write("*" + final_setting);

  }
}


void checkBox(int[] a) {
 // println(final_setting);
}