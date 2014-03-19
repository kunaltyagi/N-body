#ifndef _CELL_H_
#define _CELL_H_

#include <cmath>
#include <vector>
#include <cstdlib>

#include "particle.h"
#include "point.h"

#define G (6.673/pow(10,-11))

typedef Point Vector;

class Cell
{
private:

public:
    //std::vector<Particle> particles;
    int numberParticles;
    Particle* singleParticle;
    Cell* childOctant[8];
    Cell* parent;
    Point origin;
    Point centerOfMass;
    double mass;
    double size;
    double theta;

    Cell()
    {
        singleParticle  = NULL;
        parent          = NULL;
        centerOfMass    = Point(0, 0, 0);
        origin          = Point(0, 0, 0);
        for (int i = 0; i < 8; ++i)
        {
            childOctant[i] = NULL;
        }
        mass  = 0;
        size  = 1;
        theta = 1;
        numberParticles = 0;
    }

    Cell(double len, int x = 0, int y = 0, int z = 0, int mac = 1)
    {
        singleParticle  = NULL;
        parent          = NULL;
        centerOfMass    = Point(x, y, z);
        origin          = Point(x, y, z);
        for (int i = 0; i < 8; ++i)
        {
            childOctant[i] = NULL;
        }
        mass  = 0;
        size  = len;
        theta = mac;
        numberParticles = 0;
    }

    Cell(double len, Point p, int mac = 1)
    {
        singleParticle  = NULL;
        parent          = NULL;
        centerOfMass    = p;
        origin          = p;
        for (int i = 0; i < 8; ++i)
        {
            childOctant[i] = NULL;
        }
        mass = 0;
        size = len;
        theta = mac;
        numberParticles = 0;
    }

    Point getOrigin(int octant)
    {
        Point temp(origin);
        if(octant == 0 || octant ==3 || octant ==4 || octant ==7)
        {
            temp.x += size/2;
        }
        else
        {
            temp.x -= size/2;
        }

        if(octant ==0 || octant ==1 || octant ==4 || octant ==5)
        {
            temp.y += size/2;
        }
        else
        {
            temp.y -= size/2;
        }

        if(octant ==0 || octant ==1 || octant ==2 || octant ==3)
        {
            temp.z += size/2;
        }
        else
        {
            temp.z -= size/2;
        }
        return temp;
    }

    void insetToRoot(Particle& newParticle)
    {
        int octant;
        Point newPoint = newParticle.getPosition();
        if(numberParticles > 1)
        {
            octant = newParticle.getPosition().getOctant(origin);
            if(octant < 0)
            {
                octant = 0;
            }
            if(childOctant[octant] == NULL)
            {
                childOctant[octant] = new Cell(size/2, this->getOrigin(octant));
            }
            childOctant[octant]->insetToRoot(newParticle);
        }
        else if(numberParticles == 1)
        {
            if((singleParticle->getPosition() - newParticle.getPosition()).mod() > (singleParticle->getRadius() + newParticle.getRadius()))
            {
                octant = singleParticle->getPosition().getOctant(origin);
                if(octant < 0)
                {
                    octant = 0;
                }
                if(childOctant[octant] == NULL)
                {
                    childOctant[octant] = new Cell(size/2, this->getOrigin(octant));
                }
                childOctant[octant]->insetToRoot(*singleParticle);
                octant = newParticle.getPosition().getOctant(origin);
                if(octant < 0)
                {
                    octant = 0;
                }
                if(childOctant[octant] == NULL)
                {
                    childOctant[octant] = new Cell(size/2, this->getOrigin(octant));
                }
                childOctant[octant]->insetToRoot(newParticle);
            }
            else
            {
                //e = 0
                //implement collision?
                double newMass = singleParticle->getMass() + newParticle.getMass();
                singleParticle->updateVelocity((singleParticle->getVelocity()*singleParticle->getMass())+(newParticle.getVelocity()*newParticle.getMass())/newMass);
                singleParticle->updateAcceleration((singleParticle->getAcceleration()*singleParticle->getMass())+(newParticle.getAcceleration()*newParticle.getMass())/newMass);
                //something like it?
                //mass aggregator
                singleParticle->updateMass(newMass);
                newParticle.updateMass(0);
            }
        }
        else if(numberParticles == 0)
        {
            singleParticle = &newParticle;
        }
        ++numberParticles;
    }

    void calcMassDistribution()
    {
        if(numberParticles == 1)
        {
            centerOfMass = singleParticle->getPosition();
            mass = singleParticle->getMass();
        }
        else
        {
            for(int i = 0; i < 8; ++i)
            {
                if(childOctant[i] == NULL)
                {
                    continue;
                }
                childOctant[i]->calcMassDistribution();
                mass += childOctant[i]->mass;
                centerOfMass = centerOfMass + ( childOctant[i]->centerOfMass * childOctant[i]->mass);
            }
            centerOfMass = centerOfMass / mass;
        }
    }

    Vector calcForce(Particle target)
    {
        Vector force = Vector(0, 0, 0);
        if(numberParticles == 1)
        {
            force = (target.getPosition()-(*singleParticle).getPosition()) *G* ( (target.getMass() * (*singleParticle).getMass()) * pow((target.getPosition()-(*singleParticle).getPosition()).mod(), -3));
        }
        else
        {
            double r = (target.getPosition()-(*singleParticle).getPosition()).mod();
            double d = size;
            if (d/r < theta)
            {
              force = (target.getPosition()-centerOfMass) *G* ( (target.getMass() * mass) * pow((target.getPosition()-centerOfMass).mod(), -3));
            }
            else
            {
                for(int i = 0; i < 8; ++i)
                {
                    if(childOctant[i] == NULL)
                    {
                        continue;
                    }
                    force = force + childOctant[i]->calcForce(target);
                }
            }
        }
        return force;
    }
};

#endif
// _CELL_H_
