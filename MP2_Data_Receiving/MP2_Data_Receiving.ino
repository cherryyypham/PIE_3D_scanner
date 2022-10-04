
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
float horVal = 0;
float sensorVal = 0;                           
float verVal = 0;

//Initiating values for calculating coordinate values
int verAngle = 0;
int horAngle = 0;

int scan_begin = 1;

void setup() {
  //Attaching servos to pins
  servoPan.attach(servoPinPan);
  servoTilt.attach(servoPinTilt);

  //Begin Serial
  Serial.begin(9600);
}

void loop() { 
    while (scan_begin == 1) {
      delay(2000);
      
      servoTilt.write(0);
      servoPan.write(0);
      delay(2000);
      for (int j = 45; j <= 85; j += 5) {
        horAngle = j;
        servoPan.write(horAngle);
        delay(100);
        for (int i = 35; i <= 75; i += 5) {     //Change this number if scan is ugly
          verAngle = i;
//          Serial.print((verAngle-40)+1+31*((horAngle-50)/5)); Serial.print(" - ");
          servoTilt.write(verAngle);
          delay(100);

          //Read Distance Data from Sensor
          sensorVal = analogRead(sensorPin);
          
          //Calibrating horizontal and vertical data
          verVal = verAngle;
          horVal = horAngle;
          Serial.print(horVal); Serial.print(",");
          Serial.print(sensorVal); Serial.print(",");
          Serial.println(verVal);
          
          //Delay so data is not overwritten
          delay(100);
        }
        //Reset the vertical angle for next pan
        verAngle = 0;
      }
      //Indicate that 1 scanning session is finished
      Serial.println("Done");
      
      scan_begin = 0;
      servoTilt.write(0);
      servoPan.write(0);
    }
    
}
