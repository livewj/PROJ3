#ifndef VERLETV_H
#define VERLETV_H


class VERLETV
{
public:				  
	bool first;
    double m_dt;
    VERLETV(double dt);
    void integrateOneStep(class SolarSystem &system);
};

#endif // EULER_H
