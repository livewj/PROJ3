#include "solarsystem.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

SolarSystem::SolarSystem() :
    m_kineticEnergy(0),
    m_potentialEnergy(0)
{
}

CelestialBody& SolarSystem::createCelestialBody(vec3 position, vec3 velocity, double mass) {
    m_bodies.push_back( CelestialBody(position, velocity, mass) );
    return m_bodies.back(); // Return reference to the newest added celstial body
}

void SolarSystem::calculateForcesAndEnergy()
{

	m_kineticEnergy = 0;
    m_potentialEnergy = 0;
    m_angularMomentum.zeros();

    for(CelestialBody &body : m_bodies) {
        // Reset forces on all bodies
        body.force.zeros();
    }
	vec3 l;
	double rel;
	vec3 f;
	double dr;
    for(int i=0; i<numberOfBodies(); i++) {
        CelestialBody &body1 = m_bodies[i];
	    for(int j=i+1; j<numberOfBodies(); j++) {
            CelestialBody &body2 = m_bodies[j];
            vec3 deltaRVector = body1.position - body2.position;
            dr = deltaRVector.length();
            // Calculate the newtonian gravity force and potential energy here
			f = 4*M_PI*M_PI*body1.mass*body2.mass/(dr*dr*dr)*deltaRVector;
			if(!general){
				body2.force += f;
				if(m_fixed_sun) {
					if (i != 0){
						body1.force -= f;
						}	
					}
				else{ 
					body1.force -= f;
					}
				}

			//Here we implement newton's gravity law with added general relativistic effects in case you wanted that instead
			else{	
				l = deltaRVector.cross((body2.velocity-body1.velocity));
				rel = 1.+3.*l.lengthSquared()/(deltaRVector.lengthSquared()*63197.8*63197.8);
				body2.force += f*rel;
				if(m_fixed_sun) {
					if (i != 0){
						body1.force -= f*rel;
						}	
					}
				else{ 
					body1.force -= f*rel;
					}
				}		
				if(body1.mass == m_bodies[0].mass && body2.mass == m_bodies[1].mass){
					m_kineticEnergy += 0.5*body2.mass*(body2.velocity-body1.velocity).lengthSquared();
					m_potentialEnergy -= 4*M_PI*M_PI*body1.mass*body2.mass/dr;
					m_angularMomentum += deltaRVector.cross(body2.velocity-body1.velocity)*body2.mass;
					}
				//cout << m_kineticEnergy + m_potentialEnergy << endl;
				//cout <<body2.mass*dr* sqrt((body2.velocity+body1.velocity).lengthSquared())  << endl;
			
        }
    }
}


void SolarSystem::mass_center(){	//Calculating the mass center

	vec3 center_of_mass; //three spacial coordinates of mass center	
	double total_mass;   //sum of masses, including the sun

	for (CelestialBody& body: m_bodies){ //total masses
		total_mass += body.mass;
	}

	for (CelestialBody& body: m_bodies){ //mass center
		center_of_mass += body.mass*body.position/total_mass;

	}	

	for (CelestialBody& body: m_bodies){ //setting the mass center 
		body.position = body.position - center_of_mass;
	}
	//Giving the sun its velocity(-total_velocity/mass_sun)
	vec3 total_momentum;
	for ( CelestialBody& body: m_bodies ){
		if( &body != &m_bodies[0]){		
		total_momentum += body.mass*body.velocity;
	
		}
	}
	m_bodies[0].velocity -= total_momentum/m_bodies[0].mass;//velocity for sun around mass center

}


int SolarSystem::numberOfBodies() const
{
    return m_bodies.size();
}

double SolarSystem::totalEnergy() const
{
    return m_kineticEnergy + m_potentialEnergy;
}

double SolarSystem::potentialEnergy() const
{
    return m_potentialEnergy;
}

double SolarSystem::kineticEnergy() const
{
    return m_kineticEnergy;
}

double SolarSystem::angularMomentum() 
{
    return m_angularMomentum.length();
}

void SolarSystem::writeToFile(string filename)
{
    if(!m_file.good()) {
        m_file.open(filename.c_str(), ofstream::out);
        if(!m_file.good()) {
            cout << "Error opening file " << filename << ". Aborting!" << endl;
            terminate();
        }
    }

    m_file << numberOfBodies() << endl;
    m_file << "Comment line that needs to be here. Balle, y u do dis." << endl;
    for(CelestialBody &body : m_bodies) {
        m_file << "1 "<< setprecision(15) << body.position.x() << " " << body.position.y() << " " << body.position.z() << "\n";
    }
}


std::vector<CelestialBody> &SolarSystem::bodies()
{
    return m_bodies;
}
