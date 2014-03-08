#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <vector>

typedef INT (long long int) ;

class System
{
private:
    vector<Particle> _particles;
    Point _centerOfMass;

    double _simTime;

    double _probeInterval;

    INT _NoOfParticles;

    bool _aggregate;
    bool _collision;

    Cell* root;

    // MAC(Multi-pole Acceptance Criterion) value of $$ \theta = \frac{d}{r} $$ for a group.
    double _threshold;

public:
    System()
    {
        ;
    }
    void setNumberOfParticles(INT num)      {   _NoOfParticles  = num;          }
    void setSimTime(double totalTime)       {   _simTime        = totalTime;    }
    void setProbeInterval(double delta_t)   {   _probeInterval  = delta_t;      }
    void setCollisions(bool val)            {   _collision      = val;          }
    void setAggregation(bool val)           {   _aggregate      = val;          }
    void setMAC(double theta)               {   _threshold      = theta;        }
    void enterParticles()
    {
        _centerOfMass.x = _centerOfMass.y = _centerOfMass.z = 0;
        Particle tmp;
        Point origin;
        double e;
        double mass, radius;
        for(INT i = 0; i < _NoOfParticles; ++i)
        {
            cin>>origin.x>>origin.y>>origin.z;  tmp.updatePosition(origin);
            _centerOfMass = (_centerOfMass*i + mass*origin)/(i+1);
            cin>>mass>>radius>>e;   tmp.updateMass(mass); tmp.updateRadius(radius); tmp.updateE(e);
            cin>>origin.x>>origin.y>>origin.z;  tmp.updateVelocity(origin);
            cin>>origin.x>>origin.y>>origin.z;  tmp.updateAcceleration(origin);
            _particles.push_back(Particle(tmp));
        }
    }
    void BuildQuads()
    {
        delete root;
        root = new Cell;
        root->origin = Point(0,0,0);
        for(INT i = 0; i < _NoOfParticles; ++i)
        {
            root->insetToRoot(_particles[i]);
        }
    }
};
#endif
// _SYSTEM_H_