#Compare Earths orbit before and after Jupiter, task 3e)
from math import sqrt
import numpy as np

def read(filename):
	#function that reads the x and y coordinate
	infile = open(filename, 'r')
	Earth = []
	relevant_lines = infile.readlines()[1:] #skips the irrelevant lines
	for line in relevant_lines:
	    data = line.split()
	    Earth.append(float(data[3])) #x values
	    Earth.append(float(data[4])) #y values
	infile.close()
	Earth = np.array(Earth)
	return Earth

Earth_1 = read('positions1.txt')
Earth_2 = read('positions2.txt')

'''
print Sun[::2] #x values
print Sun[1::2] #y values
print Earth[::2] #x values
print Earth[1::2] #y values
'''

error_x = abs(Earth_1[::2] - Earth_2[::2])
error_y = abs(Earth_1[1::2] - Earth_2[1::2])

error = np.sqrt(error_x**2 + error_y**2)
print max(error)

import matplotlib.pyplot as plt
plt.plot(np.linspace(0,20,len(error)),error)
plt.xlabel('time [yr]', fontsize=16)
plt.ylabel('Error [AU]', fontsize=16)
plt.show()