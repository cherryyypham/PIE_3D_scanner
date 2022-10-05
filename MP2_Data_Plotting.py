import csv
import math
import numpy as np
import matplotlib.pyplot as plt

arr = []

pan_arr = []
val_arr = []
tilt_arr = []
x_arr = []
y_arr = []
z_arr = []
# string1 = ""

with open("data3.csv") as f:
    r2 = csv.reader(f)
    for row in r2:
        arr.append(row)

for i in arr:
    # string1 += str(i.index(j))
    pan_arr.append(i[0])
    val_arr.append(i[1])
    tilt_arr.append(i[2])
# print(string1)
# x_arr = x_arr[:958]
# y_arr = y_arr[:958]
# z_arr = z_arr[:958]

# print(arr)


# for pan in pan_arr:
#     pan = math.radians(int(pan))

# for tilt in tilt_arr:
#     tilt = math.radians(int(tilt))

# for val in val_arr:
#     val = (414091/(int(val) + 102.6) ** (1.548))

for i in range(len(pan_arr)):
    # converting polar coordinate data from arduino to cartesian
    x = (414091/(int(val_arr[i]) + 102.6) ** (1.548)) * np.sin(math.radians(int(tilt_arr[i]))) * np.cos(math.radians(int(pan_arr[i])))
    y = (414091/(int(val_arr[i]) + 102.6) ** (1.548))  * np.sin(math.radians(int(tilt_arr[i]))) * np.sin(math.radians(int(pan_arr[i])))
    z = (414091/(int(val_arr[i]) + 102.6) ** (1.548)) * np.cos(math.radians(int(tilt_arr[i])))

    x_arr.append(x)
    y_arr.append(y)
    z_arr.append(z)

fig = plt.figure()
ax = plt.axes(projection='3d')

ax.scatter(z_arr, y_arr, x_arr, c=x_arr, cmap='viridis', linewidth=0.5)

ax.set_title('Scan of Letter "M"')

plt.show()