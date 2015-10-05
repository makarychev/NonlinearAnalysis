__author__ = 'Maksym'


import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import spline

# axis_x = np.array([6, 7, 8, 9, 10, 11, 12])
# axis_y = np.array([1.53E+03, 5.92E+02, 2.04E+02, 7.24E+01, 2.72E+01, 1.10E+01, 4.70E+00])
#
# xnew = np.linspace(axis_x.min(),axis_x.max(),300)
# power_smooth = spline(axis_x,axis_y,xnew)
#
# plt.plot(xnew,power_smooth)
# plt.show()

def Plot2D(axis_x, axis_y):
    xnew = np.linspace(axis_x.min(),axis_x.max(),300)
    power_smooth = spline(axis_x,axis_y,xnew)

    plt.plot(xnew,power_smooth)
	
def Show():
    plt.show()
