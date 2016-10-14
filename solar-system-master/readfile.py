import numpy as np

def read(filename):
	#function that reads the x and y coordinate
	infile = open(filename, 'r')
	Sun = []
	Mercury =[]
	Venus = []
	Earth = []
	Mars = []
	Jupiter = []
	Saturn = []
	Uranus = []
	Neptune = []
	relevant_lines = infile.readlines()[1:] #skips the irrelevant lines
	for line in relevant_lines:
	    data = line.split()
	    Sun.append(float(data[0]))
	    Sun.append(float(data[1]))
	    Mercury.append(float(data[3]))
	    Mercury.append(float(data[4]))
	    Venus.append(float(data[6]))
	    Venus.append(float(data[7]))
	    Earth.append(float(data[9]))
	    Earth.append(float(data[10]))
	    Mars.append(float(data[12]))
	    Mars.append(float(data[13]))
	    Jupiter.append(float(data[15]))
	    Jupiter.append(float(data[16]))
	    Saturn.append(float(data[18]))
	    Saturn.append(float(data[19]))
	    Uranus.append(float(data[21]))
	    Uranus.append(float(data[22]))
	    Neptune.append(float(data[24]))
	    Neptune.append(float(data[25]))
	infile.close()
	Sun = np.array(Sun)
	Mercury = np.array(Mercury)
	Venus = np.array(Venus)
	Earth = np.array(Earth)
	Mars = np.array(Mars)
	Jupiter = np.array(Jupiter)
	Saturn = np.array(Saturn)
	Uranus = np.array(Uranus)
	Neptune = np.array(Neptune)

	return Sun, Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune

Sun, Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune = read('positions.txt')

'''
print Sun[::2] #x values
print Sun[1::2] #y values
print Earth[::2] #x values
print Earth[1::2] #y values
'''

import matplotlib.pyplot as plt
plt.plot(0,0, 'c*') #sun
plt.plot(Mercury[::2],Mercury[1::2])
plt.plot(Venus[::2],Venus[1::2])
plt.plot(Earth[::2],Earth[1::2]) #, Earth[-2], Earth[-1], 'ob')
plt.plot(Mars[::2],Mars[1::2])
plt.plot(Jupiter[::2], Jupiter[1::2]) #, Jupiter[-2], Jupiter[-1], 'og')
plt.plot(Saturn[::2],Saturn[1::2])
plt.plot(Uranus[::2],Uranus[1::2])
plt.plot(Neptune[::2],Neptune[1::2])
plt.legend(['Sun','Mercury', 'Venus', 'Earth', 'Mars', 'Jupiter', 'Saturn', 'Uranus', 'Neptune'])
plt.xlabel('x [AU]')
plt.ylabel('y [AU]')
plt.axis('equal')
plt.show()
