from matplotlib.pyplot import *
from numpy import *

file = open("positions.xyz","r")
x_sun=[]
y_sun=[]

x=[]
y=[]

i=0
for line in file:
	i+=1

	if (i-3)%4==0: #sun coordinates (x-y plane)
		x_sun.append(float(line.split()[1])) 
		y_sun.append(float(line.split()[2]))

	if i%4==0:#planet coordinates (x-y plane)
		x.append(float(line.split()[1])) 
		y.append(float(line.split()[2]))

plot(x_sun,y_sun)
plot(x,y)

xlabel("AU",fontsize=16)
ylabel("AU",fontsize=16)
show()
