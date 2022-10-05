import serial
import csv

arduinoComPort = "/dev/ttyACM0"
baudRate = 9600
serialPort = serial.Serial(arduinoComPort, baudRate, timeout=1)

pan_arr = []
val_arr = []
tilt_arr = []

take_data = True

while take_data:
  lineOfData = serialPort.readline().decode()

  if len(lineOfData) > 0:
    if "Done" in lineOfData:
      take_data = False
    else:
      pan, val, tilt = (int(float(i)) for i in lineOfData.split(','))

      # pan = math.radians(pan)
      # tilt = math.radians(tilt)
      # val = (414091/(val + 102.6) ** (1.548))

      # converting polar coordinate data from arduino to cartesian
      # x = val * np.sin(tilt) * np.cos(pan)
      # y = val * np.sin(tilt) * np.sin(pan)
      # z = val * np.cos(tilt)

      pan_arr.append(pan)
      val_arr.append(val)
      tilt_arr.append(tilt)

      print("z = " + str(pan), end="")
      print(", y = " + str(val), end="")
      print(", z = " + str(tilt))

with open("data3.csv", "w", newline = "") as f:
  writer = csv.writer(f)
  for i in range(len(pan_arr)):
    writer.writerow([pan_arr[i], val_arr[i], tilt_arr[i]])