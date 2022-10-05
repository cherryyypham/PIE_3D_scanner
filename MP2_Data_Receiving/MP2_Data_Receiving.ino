
/**
   PIE-S2 Project 2
   Name: DIY 3D Scanner
   Purpose: Move 3D scanner servos that mount an IR distance sensor, output distance reading in
   voltage along with the servos angles where each reading is recorded
   @author Miriam Rich and Cherry Pham
   @version 1.0 10/06/2022
*/

#include <Servo.h>

//Initiating servos values
Servo servoPan;
Servo servoTilt;
int servoPinPan = 9;
int servoPinTilt = 10;

//Initiating sensors values
int sensorPin = 0;
float sensorVal = 0;

//Initiating servos' angles
int verAngle = 0;
int horAngle = 0;

//Boolean indicating whether the scanning process should be running
int scan_begin = 1;

// Setup function that run once
void setup() {
  //Attaching servos to pins
  servoPan.attach(servoPinPan);
  servoTilt.attach(servoPinTilt);

  //Begin serial
  Serial.begin(9600);
}

// Loop through 3D scanner tasks (pan, tilt, read in data)
void loop() { 
    while (scan_begin == 1) {
      //Reset servos to ensure consistent behavior
      servoTilt.write(0);
      servoPan.write(0);
      delay(2000);
      //Pan loop from 35deg to 85deg
      for (int j = 35; j <= 85; j += 1) {
        horAngle = j;
        servoPan.write(horAngle);
        delay(100); //Short delay between pans for possible lagging elements to catch up
        //Tilt loop
        for (int i = 20; i <= 90; i += 1) {
          verAngle = i;
          servoTilt.write(verAngle);
          delay(100); //Short delay between tilts for possible lagging elements to catch up
                      //This delay is also crucial for the IR sensor to receive stable data
          //Take distance data 5 times to average out later for accurate/consistent readings
          for (int n = 0; n < 5; n++) {
            //Read distance data from sensor, add everything to a sum to be averaged later
            sensorVal += analogRead(sensorPin);
          }
          //Send raw data to Python so it is easier to manipulate
          Serial.print(47); Serial.print(", ");
          Serial.print(sensorVal/5); Serial.print(", ");
          Serial.println(horAngle);
          //Reset the sum of sensor output per every tilt
          sensorVal = 0;
          
          //Extra delay
          delay(100);
        }
        //Reset the vertical angle (tilt angle) for next pan
        verAngle = 0;
      }
      //Indicate that 1 scanning session is finished
      Serial.println("Done");
      //Reset scanner, end process
      scan_begin = 0;
      servoTilt.write(0);
      servoPan.write(0);
    }
    
}
