from matplotlib.pyplot import *
from numpy import *

file = open("positions.xyz","r")
i=0
r =[]
for line in file:
	i+=1	
	if (i-4)%11==0:
		r.append(sqrt(float(line.split()[1])**2 + float(line.split()[2])**2 + float(line.split()[3])**2))
n=len(r)
errors = zeros(n)
for i in range(n):
	errors[i] = r[i]-1
plot(linspace(0,100,n),errors)
xlabel("Time (100 years)",fontsize=16)
ylabel("Deviation (normalized) [AU]",fontsize=16)
show()
print mean(errors)
