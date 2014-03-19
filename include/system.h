#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <cmath>
#include <iostream>
#include <vector>

#include "cell.h"
#include "particle.h"
#include "point.h"

typedef long long int INT;
typedef Point Vector ;

class System
{
private:
    std::vector<Particle> _particles;
    Point _centerOfMass;

    double _simTime;
    double _probeInterval;
    double _threshold;    // MAC(Multi-pole Acceptance Criterion) value of $$ \theta = \frac{d}{r} $$ for a group.

    INT _NoOfParticles;

    bool _aggregate;
    bool _collision;

    Cell* root;
    double _size;

public:
    System()
    {
        _threshold = 1;
    }
    void setNumberOfParticles(INT num)      {   _NoOfParticles  = num;          }
    void setSimTime(double totalTime)       {   _simTime        = totalTime;    }
    void setProbeInterval(double delta_t)   {   _probeInterval  = delta_t;      }
    void setCollisions(bool val)            {   _collision      = val;          }
    void setAggregation(bool val)           {   _aggregate      = val;          }
    void setMAC(double theta)               {   _threshold      = theta;        }
    void setSize(double size)               {   _size           = size;         }

    void enterParticles()
    {
        _centerOfMass.x = _centerOfMass.y = _centerOfMass.z = 0;
        Particle tmp;
        Point origin;
        double e;
        double mass, radius;
        for(INT i = 0; i < _NoOfParticles; ++i)
        {
            std::cin>>origin.x>>origin.y>>origin.z;  tmp.updatePosition(origin);
            _centerOfMass = _centerOfMass + origin * mass;
            std::cin>>mass>>radius>>e;   tmp.updateMass(mass); tmp.updateRadius(radius); tmp.updateE(e);
            std::cin>>origin.x>>origin.y>>origin.z;  tmp.updateVelocity(origin);
            std::cin>>origin.x>>origin.y>>origin.z;  tmp.updateAcceleration(origin);
            _particles.push_back(Particle(tmp));
        }
        _centerOfMass = _centerOfMass / _NoOfParticles;
    }

    //at each step of computation, bloody expensive process
    void BuildQuadTree()
    {
        delete root;
        root = new Cell(_size, Point(0,0,0), _threshold);
        for(INT i = 0; i < _NoOfParticles; ++i)
        {
            root->insetToRoot(_particles[i]);
        }
    }

    void calcForce()
    {
        Vector force;
        for(INT i = 0; i < _NoOfParticles; ++i)
        {
            force = root->calcForce(_particles[i]);
            _particles[i].applyForce(force);
        }
    }

    void move()
    {
        Point temp;
        double size = _size/2;
        for(INT i = 0; i < _NoOfParticles; ++i)
        {
            _particles[i].move(_probeInterval);
            temp = _particles[i].getPosition();
            if((temp.x > size || temp.x < -size)&&(temp.y > size || temp.y < -size)&&(temp.z > size || temp.z < -size) || _particles[i].getMass() == 0)
                //out of bounds
            {
                _particles.erase(_particles.begin()+i);
            }
        }
    }
};
#endif
// _SYSTEM_H_
