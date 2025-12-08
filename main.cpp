#include <fstream>
#include <iostream>
#include <chrono> //for the clock
#include <vector>
#include "objects.h"

using namespace std;


int main(){
    using clock = chrono::high_resolution_clock; //the clock we will be using is the high resolution clock from the chrono library
    using ms = chrono::duration<double, milli>; //time will be measured using milliseconds

    const int particleCount = 1000; //how much of something do we have?
    const int numSteps = 1000; //how many steps the sim has?
    const double dt = 0.01; //change in time

    vector<Particle> particles(particleCount); //create and set particles
    for (int i = 0; i < particles.size(); i++) {
        particles[i].setPos(0.0);
        particles[i].setVel(0.0);
        particles[i].setAcc(1.0);
    }

    auto start = clock::now(); //start the clock
							   
	ofstream trajFile("trajectory.csv"); // file for logging data velocity vs position
	trajFile << "timestep,particle,x,v\n";

    //placeholder simulation loop
    for (int timestep = 0; timestep < numSteps; timestep++) {
        for (int j = 0; j < particles.size(); j++){
            Particle& p = particles[j];
            double x = p.getPos(); //simpler variables
            double v = p.getVel();
            double a = p.getAcc();

            v += a * dt; //equations for velocity and position
            x += v * dt;

            p.setVel(v); //set new position and velocity for next step
            p.setPos(x);

			trajFile << timestep << "," << j << "," << x << "," << v << "\n"; //log into file
        }
    }

    auto end = clock::now(); //stop clock

    ms timeElapsed = end - start; //how much time passed?

    cout << "Simulated " << particleCount << " particles for " << numSteps << " steps in " << timeElapsed.count() << " ms\n";
	
	ofstream timeFile("timings.csv", ios::app); //file for time vs input size?
	timeFile << particleCount << "," << numSteps << "," << dt << ","
             << timeElapsed.count() << "\n";
	timeFile.close();

    return 0;
}

