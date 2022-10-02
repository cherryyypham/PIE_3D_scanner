import math
import random
import numpy as np
from mpl_toolkits import mplot3d
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

import serial

# arduinoComPort = "/dev/ttyACM0"
# baudRate = 9600
# serialPort = serial.Serial(arduinoComPort, baudRate, timeout=1)

# while True:
#     lineOfData = serialPort.readline().decode()

fig = plt.figure()
ax = plt.axes(projection='3d')
xo = list(range(0, 100))
yo = list(range(0, 100))
zo = list(range(0, 100))

random.shuffle(xo)
random.shuffle(yo)
random.shuffle(zo)


ax.scatter(zo, yo, xo, c=xo, cmap='viridis', linewidth=0.5)

ax.set_title('Test Scan of Letter "M"')

plt.show()