#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include "celestialbody.h"
#include <vector>
#include <string>
#include <fstream>

class SolarSystem
{
public:
	bool conserved;	  //boolean for deciding wether you want to calculate energies and angular momentum (in that case, no positions for you)
	bool general;	  //boolean for deciding wether to include general relativistic effects
	bool m_fixed_sun; //boolean for deciding wether to fix the sun or not
	bool Earth;		  //boolean for adding the earth or the whole system
	bool Mercury;	  //boolean for adding Mercury
	bool Jupiter;	  //boolean for adding Jupiter and Earth
    SolarSystem();
    CelestialBody &createCelestialBody(vec3 position, vec3 velocity, double mass);
    void calculateForcesAndEnergy();
    int numberOfBodies() const;

    double totalEnergy() const;
    double potentialEnergy() const;
    double kineticEnergy() const;
    double angularMomentum();
    void mass_center();
    void writeToFile(std::string filename);
    std::vector<CelestialBody> &bodies();

private:
    std::vector<CelestialBody> m_bodies;
    vec3 m_angularMomentum;
    std::ofstream m_file;
    double m_kineticEnergy;
    double m_potentialEnergy;
};

#endif // SOLARSYSTEM_H
