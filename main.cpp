#include <iostream>
#include <chrono> //for the clock
#include <vector>
#include <cstdlib> //for random values to be used in Monte Carlo Integration
#include <ctime>
#include "objects.h"
using namespace std;

double MCDisplacement(double, double, double, int);

int main(){
    srand(time(0));  //seed with current time

    using clock = chrono::high_resolution_clock; //the clock we will be using is the high resolution clock from the chrono library
    using ms = chrono::duration<double, milli>; //time will be measured using milliseconds

    const int particleCount = 1000; //how much of something do we have?
    const int numSteps = 1000; //how many steps the sim has?
    const int samplesPerStep = 100; //how many samples are we running in each step?
    const double dt = 0.01; //change in time

    vector<Particle> particles(particleCount); //create and set particles
    for (int i = 0; i < particles.size(); i++) {
        particles[i].setPos(0.0);
        particles[i].setVel(0.0);
        particles[i].setAcc(1.0);
    }

    auto start = clock::now(); //start the clock

    //placeholder simulation loop
    for (int timestep = 0; timestep < numSteps; timestep++) {
        for (int j = 0; j < particles.size(); j++){
            Particle& p = particles[j];
            double x = p.getPos(); //simpler variables
            double v = p.getVel();
            double a = p.getAcc();

            double dx = MCDisplacement(v, a, dt, samplesPerStep);

            v += a * dt; //equations for velocity and position
            x += dx; //use monte carlo for x

            p.setVel(v); //set new position and velocity for next step
            p.setPos(x);
        }
    }

    auto end = clock::now(); //stop clock

    ms timeElapsed = end - start; //how much time passed?
    
    cout << "Final v of particle 0: " << particles[0].getVel() << '\n';
    cout << "Final x of particle 0: " << particles[0].getPos() << '\n';

    cout << "Simulated " << particleCount << " particles for " << numSteps << " steps in " << timeElapsed.count() << " ms\n";

    return 0;
}

//  ADDITIONAL FUNCTIONS 

double MCDisplacement(double v, double a, double dt, int samples) {
    double sum = 0.0;
    for (int i = 0; i < samples; i++){
        double u = (double)rand() / RAND_MAX; //random number 
        double tau = u * dt; //random time 
        double vtau = v + a * tau; 
        sum += vtau;
    }

    return dt * (sum / samples); //monte carlo displacement: dt * avg of random velocities
}
