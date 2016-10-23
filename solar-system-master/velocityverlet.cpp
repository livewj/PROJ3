#include "velocityverlet.h"
#include "solarsystem.h"

VelocityVerlet::VelocityVerlet(double dt) :
    first(true),
    m_dt(dt)
{

}

void VelocityVerlet::integrateOneStep(SolarSystem &system)
{
    //initialize forces
    if (first) {
        system.calculateForcesAndEnergy(); //jord sol //24flops
        first = false;
    }

    for(CelestialBody &body : system.bodies()) {
        body.velocity += body.force / body.mass * m_dt * 0.5;
        body.position += body.velocity*m_dt;      //6flops
    }

    system.calculateForcesAndEnergy(); //update forces //24 flops

    for(CelestialBody &body : system.bodies()) {
        body.velocity += 0.5*(body.force/body.mass)* m_dt; //4 flops (tot =58)
    }
}
