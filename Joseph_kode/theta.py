from matplotlib.pyplot import *
from numpy import *
file = open("thetan.dat","r")
theta = []
for line in file:
	theta.append(float(line.split()[0]))

x = linspace(0,3,len(theta))
plot(x,theta)
xlabel("x [Years]",size=16)
ylabel("y [Arc Seconds]",size=16)
legend()
show()
