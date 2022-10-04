import math
import numpy as np
from mpl_toolkits import mplot3d
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from MP2_Data_Processing import z_arr, y_arr, x_arr

fig = plt.figure()
ax = plt.axes(projection='3d')
ax.scatter(z_arr, y_arr, x_arr, c=x_arr, cmap='viridis', linewidth=0.5)

ax.set_title('Test Scan of Letter "M"')

plt.show()