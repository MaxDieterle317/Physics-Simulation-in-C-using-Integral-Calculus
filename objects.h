#include<iostream>

using namespace std;

class Particle {
    private:
        double position;
        double velocity;
        double acceleration;
    public:
        Particle(double position = 0.0, double velocity = 0.0, double acceleration = 0.0) //constructor
            : position(position), velocity(velocity), acceleration(acceleration) {}

        double getPos() const {return position;} //gets
        double getVel() const {return velocity;}
        double getAcc() const {return acceleration;}

        void setPos(double newPos) { position = newPos; } //sets
        void setVel(double newVel) { velocity = newVel; }
        void setAcc(double newAcc) { acceleration = newAcc; }
 
};