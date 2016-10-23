#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "solarsystem.h"
#include "verletv.h"
#include "euler.h"
#include <string>
using namespace std;

int main(int numArguments, char **arguments)
{
    int numTimesteps[] ={10,20,40,60,80,100,500,1000,5000,10000};
	double dt[] = {0.1,1/20.,1/40.,1/60.,1/80.,0.01,0.002,0.001,0.0002,0.0001};



for(int iterator = 0; iterator<10; iterator++){
	string var = "euler" + to_string(iterator);
    if(numArguments >= 2) numTimesteps[iterator] = atoi(arguments[1]);

    SolarSystem solarSystem;
    // We create new bodies like this. Note that the createCelestialBody function returns a reference to the newly created body
    // This can then be used to modify properties or print properties of the body if desired
    // Use with: solarSystem.createCelestialBody( position, velocity, mass );
	solarSystem.general = 0;				 //if you want general relativistic effects then don't set to zero
	solarSystem.m_fixed_sun = 1; //if you want to fix the sun i origo then don't set to zero

    solarSystem.createCelestialBody( vec3(0, 0, 0), vec3(0, 0, 0), 1.0 ); //Sun
	solarSystem.createCelestialBody( vec3(1, 0, 0), vec3(0, 2*M_PI, 0), 3e-6 ); //Earth



    // To get a list (a reference, not copy) of all the bodies in the solar system, we use the .bodies() function
    vector<CelestialBody> &bodies = solarSystem.bodies();

    for(int i = 0; i<bodies.size(); i++) {
        CelestialBody &body = bodies[i]; // Reference to this body
        cout << "The position of this object is " << body.position << " with velocity " << body.velocity << endl;
    }


    solarSystem.writeToFile(var);
    Euler integrator(dt[iterator]);
    for(int timestep=0; timestep<numTimesteps[iterator]; timestep++) {

        integrator.integrateOneStep(solarSystem);
        solarSystem.writeToFile(var);

		//cout <<  << endl;
    }


    cout << "I just created my 199th solar system that has " << solarSystem.bodies().size() << " objects." << endl;

}
}
