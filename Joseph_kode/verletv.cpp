#include <iostream>
#include "verletv.h"
#include "solarsystem.h"
#include <math.h>
using namespace std;
VERLETV::VERLETV(double dt) :
	first(1),
    m_dt(dt)	

{
}

void VERLETV::integrateOneStep(SolarSystem &system)
{

    if(first){               //due to the velocity verlet algorithm, multiple steps are needed
	system.calculateForcesAndEnergy(); // here we initiate the integration by calculating the forces in the system
	first = 0;			
	}

    for(CelestialBody &body : system.bodies()) {	//Here we create the new positions, but a midway velocity
		body.velocity += 0.5*body.force / body.mass * m_dt;
        body.position += body.velocity*m_dt;
		}
    	system.calculateForcesAndEnergy();					 //with a new position and a midway velocity, we create brand new forces
    for(CelestialBody &body : system.bodies()) {
        body.velocity += 0.5*body.force / body.mass * m_dt;  //Here we finalize the velocity with our new forces/accelerations
		
		}

    }

