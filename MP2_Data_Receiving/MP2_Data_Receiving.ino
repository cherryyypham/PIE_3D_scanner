
/**
   PIE-S2 Project 2
   Name: DIY 3D Scanner
   Purpose: Create a 3D visual representation of a letter using a pan/tilt mechanism of 2 servos mounting an IR Distance Sensor

   @author Miriam Rich and Cherry Pham
   @version 1.0 10/03/2022
*/

#include <Servo.h>

//Initiating servos values
Servo servoPan;
Servo servoTilt;
int servoPinPan = 9;
int servoPinTilt = 10;

//Initiating sensor and coordinate values
int sensorPin = 0;
float xVal = 0;
float yVal = 0;                           
float zVal = 0;

//Initiating values for calculating coordinate values
int verAngle = 0;
int horAngle = 0;
int panPane = 500;                          //Estimating 5cm
int sensorLength = 200; 

void setup() {
  //Attaching servos to pins
  servoPan.attach(servoPinPan);
  servoTilt.attach(servoPinTilt);

  //Begin Serial
  Serial.begin(9600);
}

void loop() { 
    servoTilt.write(0);
    servoPan.write(0);
    delay(2000);
    for (int j = 50; j <= 80; j += 5) {
      horAngle = j;
      Serial.print("Pan Angle: "); Serial.println(horAngle);
      servoPan.write(horAngle);
      delay(100);
      for (int i = 40; i <= 70; i += 1) {     //Change this number if scan is ugly
        verAngle = i;
        servoTilt.write(verAngle);
        
        //Read Distance Data from Sensor
        yVal = analogRead(sensorPin);
        delay(100);
        
        //Calibrating horizontal and vertical data
        xVal = sin(verAngle) * panPane;
        zVal = sin(horAngle) * sensorLength;
        Serial.print(xVal); Serial.print(",");
        Serial.print(yVal); Serial.print(", ");
        Serial.println(zVal);
        
        //Delay so data is not overwritten
        delay(100);
      }
      
      //Reset the vertical angle for next pan
      verAngle = 0;
    }
}
