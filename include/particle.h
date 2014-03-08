#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <cmath>
#include <vector>

#define particleMass 1
#define particleRadius 1

typedef Point Vector ;

class Particle
{
private:
    // physical description of particle
    Point _position;
    double _mass;
    double _radius;

    // additional information about the particle
    // array for Runga-Kutta methods, stores past n values for different methods
    Vector _velocity;
    Vector _acceleration;

    std::vector<Vector> _vectVelocity;
    std::vector<Vector> _vectAcceleration;

    // supplementary information
    Cell* _parentCell;      //can it be calculated?

    // to further reduce calculations
    double _timeStep;

    // order of largest computations
    int maxN;

public:
    Particle();
    Particle(double position, double mass = particleMass, double radius = particleRadius, double velocity = 0 , double acceleration = 0);

    // main function for simulation
    /**
     * @brief move using the acceleration and velocity values
     *
     * @param t global time, with some offset
     *
     * @return move successful or not
     */
    bool move(double t)
    {
        /*
double Particle::move(double t){
        Point p;
        p.x = _velocity.x*t + _acceleration.x*t*t/2;
        p.y = _velocity.y*t + _acceleration.y*t*t/2;
        _position = (_position + p);
    }
        */
        if(fmod(t,_timeStep) == 0)
        {
            ;
        }
        else
        // out of timeStep, no need to sync yet
        {
            return false;
        }
        return true;
    }

    // setter functions
    void updateVelocity(Vector velocity)            {   _velocity       = velocity;     }
    void updateAcceleration(Vector acceleration)    {   _acceleration   = acceleration; }
    void updatePosition(Point point)                {   _position       = position;     }
    void updateTimeStep(double timeStep)            {   _timeStep       = timeStep;     }

    // getter func
    Point getPosition()         {   return _position;       }
    double getAcceleration()    {   return _acceleration;   }
    double getVelocity()        {   return _velocity;       }
    double getRadius()          {   return _radius;         }
    double getMass()            {   return _mass;           }

};
#endif
