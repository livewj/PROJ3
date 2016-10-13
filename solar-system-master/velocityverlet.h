#ifndef VELOCITYVERLET_H
#define VELOCITYVERLET_H

class VelocityVerlet
{
public:
    bool first;
    double m_dt;
    VelocityVerlet(double dt);
    void integrateOneStep(class SolarSystem &system);
};

#endif // VELOCITYVERLET_H


