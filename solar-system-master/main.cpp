#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "solarsystem.h"
#include "euler.h"
#include "velocityverlet.h"
#include <time.h> //for time-taking
using namespace std;

int main(int numArguments, char **arguments)
{
    int numTimesteps = 16000;
    if(numArguments >= 2) numTimesteps = atoi(arguments[1]);

    SolarSystem solarSystem;
    // We create new bodies like this. Note that the createCelestialBody function returns a reference to the newly created body
    // This can then be used to modify properties or print properties of the body if desired
    // Use with: solarSystem.createCelestialBody( position, velocity, mass );

    //CelestialBody &sun = solarSystem.createCelestialBody( vec3(0,0,0), vec3(0,0,0), 1.0 );

    // We don't need to store the reference, but just call the function without a left hand side

    CelestialBody &sun = solarSystem.createCelestialBody( vec3(0, 0, 0), vec3(0, 0, 0), 1.0 ); //Sun
    solarSystem.createCelestialBody( vec3(-3.299771220462327E-01, 1.314596035268270E-01, 4.090462570196151E-02), vec3(-1.589188578333726E-02, -2.505974994975800E-02, -5.904299543073971E-04)*365, 1.66E-7); //Mercury
    solarSystem.createCelestialBody( vec3(1.619559463687653E-01, -7.064885525743501E-01, -1.903349841875333E-02), vec3(1.960339728192615E-02, 4.341740156278193E-03, -1.071874641156530E-03)*365, 2.45E-6 ); //Venus
    solarSystem.createCelestialBody( vec3(9.419288875250327E-01, 3.422743349115224E-01, -1.774653038679687E-04), vec3(-6.128263831462272E-03, 1.611761267097599E-02, 1.349643765318894E-07)*365, 3e-6 ); //Earth (NASA)
    solarSystem.createCelestialBody( vec3(1.145481237413500, -7.759469057667274E-01, -4.451643705572472E-02), vec3(8.418288645937397E-03, 1.276419831984888E-02, 6.072729084019031E-05)*365, 3.23E-7); //Mars
    solarSystem.createCelestialBody( vec3(-5.429616996509673E+00, -4.392482185767863E-01, 1.232526518227290E-01), vec3(5.206515353907882E-04, -7.164038754622682E-03, 1.814205403145239E-05)*365, 9.5E-4); //Jupiter (NASA)
    solarSystem.createCelestialBody( vec3(-2.277305999381926, -9.772253310113138, 2.605465118509321E-01), vec3(5.126703359538530E-03, -1.283735869751270E-03, -1.816227490732958E-04)*365, 2.85E-4 ); //Saturn
    solarSystem.createCelestialBody( vec3(1.846626259319022E+01, 7.554511790954641, -2.111764845597773E-01), vec3(-1.517937917646755E-03, 3.456908604164539E-03, 3.251073912887524E-05)*365, 4.37E-5 ); //Uranus
    solarSystem.createCelestialBody( vec3(2.825889439040351E+01, -9.928255088021324, -4.468016759479966E-01), vec3(1.019309416815733E-03, 2.979917067133604E-03, -8.498151187073363E-05)*365, 5.15E-5); //Neptune


    vec3 total_momentum;
    for ( CelestialBody& body: solarSystem.bodies() ) {
        if (&body != &sun) {
            total_momentum += body.mass*body.velocity;
        }
    }

    sun.velocity -= total_momentum/sun.mass;

    // To get a list (a reference, not copy) of all the bodies in the solar system, we use the .bodies() function
    vector<CelestialBody> &bodies = solarSystem.bodies();

    for(int i = 0; i<bodies.size(); i++) {
        CelestialBody &body = bodies[i]; // Reference to this body
        cout << "The position of this object is " << body.position << " with velocity " << body.velocity << endl;
    }

    double dt = 0.001;
    VelocityVerlet integrator(dt);

    //start timer
    double CPU_time;
    clock_t start, finish;
    start = clock();

    for(int timestep=0; timestep<numTimesteps; timestep++) {
        integrator.integrateOneStep(solarSystem);
        solarSystem.writeToFile("positions.txt");
    }

    //stop timer
    finish = clock();
    CPU_time = ((double) (finish - start)/CLOCKS_PER_SEC );


    cout << "I just created my first solar system that has " << solarSystem.bodies().size() << " objects." << endl;
    cout << "CPU-time: " << CPU_time << endl;
    return 0;
}

