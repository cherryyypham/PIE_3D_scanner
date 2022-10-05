"""
Read and append data received through the .ino code embedded in the Arduino hardware into
a designated empty csv file.
"""

import serial
import csv

# Indicate the port connection between the device hosting the code and the Arduino board
arduinoComPort = "/dev/ttyACM0"
# Has to be the same baudRate with the code in the '.ino' file in order to take data from
# its serial monitor
baudRate = 9600
# Initiating serial port
serialPort = serial.Serial(arduinoComPort, baudRate, timeout=1)

# Initiating arrays for pan, tilt, and sensor values recorded through the '.ino' file
pan_arr = []
val_arr = []
tilt_arr = []

# Boolean of whether new data should be read in
take_data = True

# If new data should be read in
while take_data:
  # Read data from the serial port line by line
  lineOfData = serialPort.readline().decode()
  # If the line has value,
  if len(lineOfData) > 0:
    # and that value is "Done", stop taking data
    if "Done" in lineOfData:
      take_data = False
    # and that value is not "Done", indicating the end of a scanning session
    else:
      # Split values in 3 parts: pan angle, sensor output, and tilt angle
      pan, val, tilt = (int(float(i)) for i in lineOfData.split(', '))
      # Append that value to existing storage array
      pan_arr.append(pan)
      val_arr.append(val)
      tilt_arr.append(tilt)
      # Print things out in terminal to check that the data is going well while scanning
      print("z = " + str(pan), end="")
      print(", y = " + str(val), end="")
      print(", z = " + str(tilt))

# Append data to a designated empty csv file
with open("PIE_3D_scanner/data6.csv", "w", newline = "") as f:
  writer = csv.writer(f)
  for i in range(len(tilt_arr)):
    writer.writerow([pan_arr[i], val_arr[i], tilt_arr[i]])