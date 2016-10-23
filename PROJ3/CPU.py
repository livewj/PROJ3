#CPU-time graph

numTimesteps = [1e3, 1e4, 1e5, 1e6, 1e7]
CPU_VV = [0.0005312, 0.004471, 0.0464844, 0.467712, 4.57939]
CPU_E = [0.0004986, 0.0033291, 0.0353204, 0.341174, 3.29547]

import matplotlib.pyplot as plt

plt.plot(numTimesteps, CPU_VV, numTimesteps, CPU_E)
plt.xlabel('numTimesteps')
plt.ylabel('CPU-time [s]')
plt.legend(['Velocity Verlet', 'Euler'], loc=2)
plt.show()