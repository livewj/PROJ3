from matplotlib.pyplot import *
from numpy import *
file = open("conserved.dat","r")
ang = []
ene =[]

for line in file:
	ang.append(float(line.split()[0]))
	ene.append(float(line.split()[1]))

x = linspace(0,100,len(ang))
plot(x,ang,label ="Angular Momentum")
plot(x,ene,label="Total Energy")
title("Angular Momentum [$AU^2M_{\odot}$/Year] and Total Energy [$AU^2M_{\odot}$/Year^2]")
xlabel("[Years]",size=16)
ylabel("[$AU^2M_{\odot}$/Year] \
and [$AU^2M_{\odot}$/Year^2] ",size=16)
legend()
show()
