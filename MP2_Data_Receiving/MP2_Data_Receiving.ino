
/**
   PIE-S2 Project 2
   Name: DIY 3D Scanner
   Purpose: Create a 3D visual representation of a letter using a pan/tilt mechanism of 2 servos mounting an IR Distance Sensor

   @author Miriam Rich and Cherry Pham
   @version 1.0 10/03/2022
*/

#include <Servo.h>

//Initiating servos values
Servo servo1;
Servo servo2;
int servoPin1 = 9;
int servoPin2 = 10;

//Initiating sensor values
int sensorPin = 0;
int sensorValue = 0;

void setup() {
  //Attaching servos to pins
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);

  //Begin Serial
  long baudRate = 9600;     //Same baudRate with Python file
  Serial.begin(baudRate);

}

void loop() {
  //Read Distance Data from Sensor
  sensorValue = analogRead(sensorPin);

  while(true) {
    //Calibrating data
//    val = 0;
    Serial.print(sensorValue)
    delay(500);
  }
}
