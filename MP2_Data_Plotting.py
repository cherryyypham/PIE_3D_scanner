"""
Read data from a csv file with n lines of data, each line has a format of 'a,b,c'.
Convert that data into plottable points and plot them in a 3D space.
"""

import csv
import math
import matplotlib.pyplot as plt

# Initial declare for the arrays containing point values for plotting
x_arr = []
y_arr = []
z_arr = []

# Calibration equation from voltage to distance obtained from MATLAB curve-fitting function
def voltage_to_distance(x):
    return 0.0001766*(x**2) - 0.2427*x + 97.34

# Short hand for getting the cosine of an angle, with x being an angle value in degrees
def cos_of(x):
    return math.cos(math.radians(x))

# Short hand for getting the sine of an angle, with x being an angle value in degrees
def sin_of(x):
    return math.sin(math.radians(x))

# Open csv file with desired data
with open("data6.csv") as f:
    r2 = csv.reader(f)
    # Scan in every row, with each row format being [x,y,z]
    for row in r2:
        # Only get data from desired range, the letter should be somewhere between 27-37cm away from
        # the IR distance sensor
        if voltage_to_distance(int(row[1])) > 27 and voltage_to_distance(int(row[1])) < 37:
            # Convert polar coordinates into cartesian
            x_coord = sin_of(int(row[2])) * cos_of(int(row[0])-60) * voltage_to_distance(int(row[1]))
            y_coord = sin_of(int(row[2])) * sin_of(int(row[0])-60) * voltage_to_distance(int(row[1]))
            z_coord = cos_of(int(row[2])) * voltage_to_distance(int(row[1]))
            # Add everything of the same type to an array for plotting
            x_arr.append(x_coord)
            y_arr.append(y_coord)
            z_arr.append(z_coord)
# Plot the 3D representation of the letter from collected sensor data using a scatterplot
fig = plt.figure()
ax = plt.axes(projection='3d')
ax.scatter(x_arr, y_arr, z_arr, cmap=plt.get_cmap('jet'), linewidth=0.5)
ax.set_title('Scan of letter "L"')
plt.show()