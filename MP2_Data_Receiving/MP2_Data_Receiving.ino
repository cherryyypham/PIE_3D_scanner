
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

//Initiating sensor values
int sensorPin = 0;
int sensorValue = 0;

//Initiating coordinate values
float xVal = 0;
float yVal = 100;                           //Estimating 1cm 
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
  long baudRate = 9600;                     //Same baudRate with Python file
  Serial.begin(baudRate);

}

void loop() { 
  while(true) {
    for (int j = 0; j <= 180; j += 10) {
      horAngle = -90 + j;
      servoPan.write(horAngle);
      delay(100);
      for (int i = 0; i <= 180; i += 10) {
        verAngle = -90 + i;
        servoTilt.write(verAngle);
        //Read Distance Data from Sensor
        sensorValue = analogRead(sensorPin);
        if (sensorValue >= 300){
          //Calibrating horizontal and vertical data
          xVal = sin(verAngle) * panPane;
          zVal = sin(horAngle) * sensorLength;
          Serial.print(xVal); Serial.print(",");
          Serial.print(yVal); Serial.print(",");
          Serial.println(zVal);
          //Delay so data is not overwritten
          delay(500);
        }
      }
      //Reset the vertical angle for next pan
      verAngle = 0;
    }
    
  }
}
