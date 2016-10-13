#include "solarsystem.h"
#include <iostream>
#include <cmath>
#include <iomanip>
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

    for(int i=0; i<numberOfBodies(); i++) {
        CelestialBody &body1 = m_bodies[i];
        for(int j=i+1; j<numberOfBodies(); j++) {
            CelestialBody &body2 = m_bodies[j];
            vec3 deltaRVector = body1.position - body2.position;
            double dr = deltaRVector.length();
            // Calculate the force and potential energy here
            body2.force += 4*M_PI*M_PI*body1.mass*body2.mass/(dr*dr*dr) * deltaRVector; //gravitational force

            if (i != 0) //Sun is fixed
            {
                body1.force -= 4*M_PI*M_PI*body1.mass*body2.mass/(dr*dr*dr) * deltaRVector; }

            m_kineticEnergy += 0.5*body2.mass*(body2.velocity + body1.velocity).lengthSquared();
            m_potentialEnergy -= 4*M_PI*M_PI*body1.mass*body2.mass/dr;
            //cout << m_kineticEnergy + m_potentialEnergy << endl;  //remains constant

            m_angularMomentum = dr*body2.mass*(body2.velocity+body1.velocity);
            //cout << m_angularMomentum.lengthSquared() << endl; //constant

        }



    }
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

void SolarSystem::writeToFile(string filename)
{
    if(!m_file.good()) {
        m_file.open(filename.c_str(), ofstream::out);
        if(!m_file.good()) {
            cout << "Error opening file " << filename << ". Aborting!" << endl;
            terminate();
        }
    }

    m_file << endl;
    for(CelestialBody &body : m_bodies) {
        m_file << setprecision(15) << body.position.x() << " " << body.position.y() << " " << body.position.z() << " "; // "\n";
    }
}

vec3 SolarSystem::angularMomentum() const
{
    return m_angularMomentum;
}

std::vector<CelestialBody> &SolarSystem::bodies()
{
    return m_bodies;
}
