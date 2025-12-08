#include <iostream>
#include <chrono> //for the clock
#include <vector>
#include <cstdlib> //for random values to be used in Monte Carlo Integration
#include <ctime>
#include "objects.h"
using namespace std;

double MCDisplacement(double, double, double, int);

int main() {
    srand(time(0));  //seed with current time

    using clock = chrono::high_resolution_clock; //the clock we will be using is the high resolution clock from the chrono library
    using ms = chrono::duration<double, milli>; //time will be measured using milliseconds

    int particleCount;       // how many particles?
    int numSteps;            // how many time steps?
    const double dt = 0.01;  // change in time
    double acceleration; 
    int samplesPerStep; //how many samples are we running in each step?

    do {
        cout << "Enter number of particles (must be greater than 0): ";
        cin >> particleCount;
        if (particleCount <= 0) {
            cout << "Invalid input. Please enter a positive integer.\n";
        }
    } while (particleCount <= 0);

    do {
        cout << "Enter number of time steps (must be greater than 0): ";
        cin >> numSteps;
        if (numSteps <= 0) {
            cout << "Invalid input. Please enter a positive integer.\n";
        }
    } while (numSteps <= 0);
    
    cout << "Enter particle acceleration: ";
    cin >> acceleration;

    do {
        cout << "Monte Carlo integration takes the average of a certain number of samples.\n";
        cout << "Enter sample count (must be greater than 0): ";
        cin >> samplesPerStep;
        if (samplesPerStep <= 0) {
            cout << "Invalid input. Please enter a positive integer.\n";
        }
    } while (samplesPerStep <= 0);
    
    vector<Particle> particles(particleCount); //create and set particles
    for (int i = 0; i < particles.size(); i++) {
        particles[i].setPos(0.0);
        particles[i].setVel(0.0);
        particles[i].setAcc(acceleration);
    }

    cout << "\n----- Simulation Settings -----\n"; //adds some flair to the UI
    cout << "Particles:      " << particleCount << '\n';
    cout << "Time steps:     " << numSteps << '\n';
    cout << "dt:             " << dt << '\n';
    cout << "Acceleration:   " << acceleration << '\n';
    cout << "Samples/step:   " << samplesPerStep << '\n';
    cout << "-------------------------------\n\n";

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

    double T = numSteps * dt; //total time
    double exactVel = acceleration * T; //exact velocity
    double exactPos = 0.5 * acceleration * T * T; //exact position

    double simVel = particles[0].getVel();
    double simPos = particles[0].getPos();

    double velError = simVel - exactVel;
    double posError = simPos - exactPos;

    cout << "\n----------- Results -----------\n";
    cout << "Exact final velocity:   " << exactVel << '\n';
    cout << "Simulated final velocity: " << simVel << '\n';
    cout << "Velocity error:         " << velError << "\n\n";

    cout << "Exact final position:   " << exactPos << '\n';
    cout << "Simulated final position: " << simPos << '\n';
    cout << "Position error:         " << posError << "\n";
    cout << "-------------------------------\n\n";


    cout << "Simulated " << particleCount << " particles for "
        << numSteps << " steps in " << timeElapsed.count() << " ms\n\n";

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
