FYS3150/FYS4150 - Project 3 class
============
This is a simple example implementing most classes you need in order to do project 3 in FYS3150/FYS4150. 

I've built my new clas on top of this example. It now includes more writing options and a velocity Verlet algorithm.

Code name and use:

#Class files + main and write.cpp
euler.cpp/h    ===   Euler Method
verletv.cpp/h  ===   Verlet Method
celestialbody.cpp/h === Creates Planets and Sun
solarsystem.cpp/h   === Inhabits the methods to calculate forces, energy etc.
vec3.cpp/h     ===   Vector class for vectorization purposes
write.cpp      ===   writes multiple files of positions in one execution
main.cpp       ===   boss, decides what to simulate or calculate through booleans

#Plotting scripts for illustrating conservation of energy, general movement, perihelion precession and error/deviation:
conservation.py, 2plots.py, theta.py, error.py === means of plotting what their names imply.
