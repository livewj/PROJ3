#This program calculates and illustrates the error factor of the Euler and Velocity Verlet method

from matplotlib.pyplot import *
from numpy import *
error_of_dt=[]

dt = [0.1,1/20.,1/40.,1/60.,1/80.,0.01,0.002,0.001,0.0002,0.0001]
for filenumber in ["0","1","2","3","4","5","6","7","8","9"]:
	method = "euler" #string
	file = open(method+filenumber,"r")
	num_lines = 0
	for line in file:
		num_lines +=1
	file.close()
	file = open(method+filenumber,"r")
	r = zeros(num_lines/4)
        x = zeros(num_lines/4)
        y = zeros(num_lines/4)


	i = 0
	j=0

	for line in file:
		i+=1
		if i%4==0:
			x[j] =float(line.split()[1])
			y[j] =float(line.split()[2])
			r[j] = sqrt(x[j]**2+y[j]**2)
			j+=1
	errors = zeros(num_lines/4-1)
	for i in range(num_lines/4-1):
		errors[i] = abs(1-r[i])
	error_of_dt.append(log10(max(errors)))


dt = log10(sorted(dt))
error_of_dt = sorted(error_of_dt)
plot(dt,error_of_dt)

xlabel("dt, [log10(years)]]",fontsize=16)
ylabel(" Global Error of dt, [log10(AU)]",fontsize=16)
print "The " + method +" method gives a global error powered by ", (error_of_dt[-1]-error_of_dt[0])/(dt[-1]-dt[0]), "[n]"
show()
#Run example for variable "method" = "euler" #(string)
'''
$ python error.py 
The euler method gives a global error powered by  0.889819931733 [n]
'''
#Run example for variable "method" = "verletv" #(string)
'''
$ python error.py 
The verletv method gives a global error powered by  1.99194856078  [n]
'''
