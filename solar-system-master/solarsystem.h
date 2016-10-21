#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include "celestialbody.h"
#include <vector>
#include <string>
#include <fstream>

class SolarSystem
{
public:
    SolarSystem();
    CelestialBody &createCelestialBody(vec3 position, vec3 velocity, double mass);
    void calculateForcesAndEnergy();
    void mass_center();
    int numberOfBodies() const;
    bool general;
    bool m_fixed_sun;
    bool Earth;
    bool Mercury;
    bool Jupiter;

    double totalEnergy() const;
    double potentialEnergy() const;
    double kineticEnergy() const;
    void writeToFile(std::string filename);
    vec3 angularMomentum() const;
    std::vector<CelestialBody> &bodies();

private:
    std::vector<CelestialBody> m_bodies;
    vec3 m_angularMomentum;
    std::ofstream m_file;
    double m_kineticEnergy;
    double m_potentialEnergy;

};

#endif // SOLARSYSTEM_H
