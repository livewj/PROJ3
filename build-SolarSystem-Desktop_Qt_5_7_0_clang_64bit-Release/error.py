#Compare Earths orbit before and after Jupiter, task 3e) and 3f) and  3g)
from math import sqrt
import numpy as np

def read(filename):
	#function that reads the x and y coordinate
	infile = open(filename, 'r')
	E = [] #coordinates
	relevant_lines = infile.readlines()[1:] #skips the irrelevant lines
	for line in relevant_lines:
	    data = line.split()
	    E.append(float(data[3])) #x values
	    E.append(float(data[4])) #y values
	infile.close()
	E = np.array(E)
	return E

#Earth_1 = read('positions3e_noJ.txt') #before Jupiter
#Earth_2 = read('positions3e_wJ.txt') #after Jupiter
M = read('positions3g_perihel.txt')  #Mercury


'''
#3e) Earth and Jupiters orbit
#E,J = read('positions3e_wJ.txt')
import matplotlib.pyplot as plt
plt.plot(0,0,'*c', E[::2], E[1::2], J[::2], J[1::2])
plt.legend(['Sun', 'Earh', 'Jupiter'])
plt.xlabel('x [AU]', fontsize=16)
plt.ylabel('y [AU]', fontsize=16)
plt.axis('equal')
plt.show()
'''
import matplotlib.pyplot as plt
#plt.plot(np.linspace(0,500,len(error)),error)
#plt.plot(np.linspace(0,100,len(Earth_2)/2),np.sqrt(Earth_2[::2]**2+ Earth_2[1::2]**2)-1)
plt.plot(M[::2], M[1::2])
plt.xlabel('time [yr]', fontsize=16)
plt.ylabel('Deviation [AU]', fontsize=16)
#plt.axis('equal')
plt.show()
