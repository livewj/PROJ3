#include <iostream>
#include <cmath>
#include <math.h>
#include <stdlib.h>
#include "solarsystem.h"
#include "verletv.h"
#include "euler.h"
#include <string>
#include <fstream>
using namespace std;

int main(int numArguments, char **arguments)
{
    long int numTimesteps = 400000;
	double dt = 0.0001;


    if(numArguments >= 2) numTimesteps = atoi(arguments[1]);


    SolarSystem solarSystem;
	CelestialBody &sun = solarSystem.createCelestialBody( vec3(0, 0, 0), vec3(0, 0, 0), 1.0 ); //Sun

    // We create new bodies like this. Note that the createCelestialBody function returns a reference to the newly created body
    // This can then be used to modify properties or print properties of the body if desired
    // Use with: solarSystem.createCelestialBody( position, velocity, mass );

	//keep this zero if you want to simulate and save positions.
	solarSystem.conserved = 0; //set non-zero if you want to measure earth's energy and angular momentum
	
	//One of the following 3 booleans must be non-zero, or else you get the entire solar system.

	solarSystem.Earth = 1;   //if you want earth and sun only then don't set to zero
	solarSystem.Mercury =1; //if you want mercury and sun only then don't set to zero
	solarSystem.Jupiter =1; //if you want Jupiter, earth and sun only then don't set to zero

	//Do you want to add general relativistic effects to the gravitational forces?
	solarSystem.general = 0;				 //if you want general relativistic effects then don't set to zero


	//The following variable decides wether you want a fixed sun in origo, and 
	//if not, delivers the sun an initial velocity while creating a new origo in the center of mass
	solarSystem.m_fixed_sun = 0; //if you want to fix the sun i origo then don't set to zero



	//The boolean expressions will now decide what kind of system you've chosen
	if(solarSystem.Mercury && !solarSystem.Earth && !solarSystem.Jupiter){
		solarSystem.createCelestialBody( vec3(0.3075, 0, 0), vec3(0,12.44,0),1.66E-7); //Mercury
	}
	
	else if (!solarSystem.Mercury && solarSystem.Jupiter){		
    	solarSystem.createCelestialBody( vec3(1, 0, 0), vec3(0, 2*M_PI, 0), 3e-6 ); //Earth
    	solarSystem.createCelestialBody( vec3(5.2, 0, 0), vec3(0, 2*M_PI/sqrt(5.2), 0), 9.5E-4 ); //jupiter

	}
	
	else if(!solarSystem.Mercury && solarSystem.Earth && !solarSystem.Jupiter){
    	solarSystem.createCelestialBody( vec3(1, 0, 0), vec3(0, 2*M_PI, 0), 3e-6 ); //Earth
	}
	else{
		solarSystem.createCelestialBody( vec3(-3.299771220462327E-01, 1.314596035268270E-01, 4.090462570196151E-02), vec3(-1.589188578333726E-02, -2.505974994975800E-02, -5.904299543073971E-04)*365, 1.66E-7); //Mercury
		solarSystem.createCelestialBody( vec3(1.619559463687653E-01, -7.064885525743501E-01, -1.903349841875333E-02), vec3(1.960339728192615E-02, 4.341740156278193E-03, -1.071874641156530E-03)*365, 2.45E-6 ); //Venus
		solarSystem.createCelestialBody( vec3(9.419288875250327E-01, 3.422743349115224E-01, -1.774653038679687E-04), vec3(-6.128263831462272E-03, 1.611761267097599E-02, 1.349643765318894E-07)*365, 3e-6 ); //Earth (NASA)
		solarSystem.createCelestialBody( vec3(1.145481237413500, -7.759469057667274E-01, -4.451643705572472E-02), vec3(8.418288645937397E-03, 1.276419831984888E-02, 6.072729084019031E-05)*365, 3.23E-7); //Mars
		solarSystem.createCelestialBody( vec3(-5.429616996509673E+00, -4.392482185767863E-01, 1.232526518227290E-01), vec3(5.206515353907882E-04, -7.164038754622682E-03, 1.814205403145239E-05)*365, 9.5E-4); //Jupiter (NASA)
		solarSystem.createCelestialBody( vec3(-2.277305999381926, -9.772253310113138, 2.605465118509321E-01), vec3(5.126703359538530E-03, -1.283735869751270E-03, -1.816227490732958E-04)*365, 2.85E-4 ); //Saturn
		solarSystem.createCelestialBody( vec3(1.846626259319022E+01, 7.554511790954641, -2.111764845597773E-01), vec3(-1.517937917646755E-03, 3.456908604164539E-03, 3.251073912887524E-05)*365, 4.37E-5 ); //Uranus
		solarSystem.createCelestialBody( vec3(2.825889439040351E+01, -9.928255088021324, -4.468016759479966E-01), vec3(1.019309416815733E-03, 2.979917067133604E-03, -8.498151187073363E-05)*365, 5.15E-5); //Neptune
	}



	//If the sun wasn't fixed, we'll set origo in the mass center instead, giving an initial velocity for the sun
	if(!solarSystem.m_fixed_sun){	
	solarSystem.mass_center();
	}

    // To get a list (a reference, not copy) of all the bodies in the solar system, we use the .bodies() function
    vector<CelestialBody> &bodies = solarSystem.bodies();

    for(int i = 0; i<bodies.size(); i++) {
        CelestialBody &body = bodies[i]; // Reference to this body
        cout << "The position of this object is " << body.position << " with velocity " << body.velocity << endl;
    }


	//Integrating and writing
	VERLETV integrator(dt);

	if(solarSystem.conserved){
		fstream Outfile;
		Outfile.open("conserved.dat",ios::out);

		for(int timestep=0;timestep < numTimesteps;timestep++ ){
				integrator.integrateOneStep(solarSystem);
				Outfile << solarSystem.angularMomentum() <<" "<<solarSystem.totalEnergy() <<endl;
				}
	}
	else if(solarSystem.Earth && solarSystem.Jupiter){
		for(int timestep=0;timestep < numTimesteps;timestep++ ){
				integrator.integrateOneStep(solarSystem);
				solarSystem.writeToFile("positions.xyz");  //comment this out if you don't want to write to file
				}
	}	
	else{

		fstream Outfile;
		Outfile.open("thetan.dat",ios::out);


		// Set some helper variables before we start the time integration.
		double thetaPrevious 	= 0;	// The perihelion angle of the previous time step.
		double theta 		= 0;	// The perihelion angle of the current time step.

		double rPreviousPrevious 	= 0;	// Mercury-Sun-distance two times steps ago.
		double rPrevious   	 	= 0;	// Mercury-Sun-distance of the previous time step.
		double r 		 	= 0;	// Mercury-Sun-distance of the current time step.

		// This is the integration loop, in which you advance the solution (usually via a integrateOneStep()
		// function located in an integrator object, e.g. the Verlet class).
		for (int timeStep = 0; timeStep < numTimesteps; timeStep++) {
	
			// Integrate the solution one step forward in time, using the GR corrected force calcuation
			// and the Verlet algorithm.
			integrator.integrateOneStep(solarSystem);

			// Compute the current perihelion angle, using the inverse tangent function from cmath.
			// This assumes there is a vector of planets, called m_bodies, available, in which the 
			// Sun is m_bodies[0] and Mercury is m_bodies[1].
			double x = bodies[1].position.x() - bodies[0].position.x();
			double y = bodies[1].position.y() - bodies[0].position.y();
			theta = atan2( y, x );

			// Compute the current Mercury-Sun distance. 
			double r = (bodies[1].position.length() - bodies[0].position).length();
	
			// Check if the *previous* time step was a minimum for the Mercury-Sun distance. I.e. check
			// if the previous distance is smaller than the current one *and* the previous previous one.
			if ( r > rPrevious && rPrevious < rPreviousPrevious ) {

				// If we are perihelion, print angle (in radians) to terminal. 
				cout << "Perihelion angle: " << thetaPrevious*180*3600/M_PI << endl;
				Outfile << thetaPrevious*180.*3600./M_PI << endl;
				// Here you should also probably write it to file for later plotting or something.
			}
		

			// Update the helper variables (current, previous, previousPrevious).
			rPreviousPrevious 	= rPrevious;
			rPrevious			= r;
			thetaPrevious		= theta;	
		}
	}
}
