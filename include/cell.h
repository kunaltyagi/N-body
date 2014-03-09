#ifndef _CELL_H_
#define _CELL_H_

#include <cmath>
#include <vector>

#include "particle.h"
#include "point.h"

class Cell
{
private:

public:
    Cell()
    {
        singleParticle  = parent    = NULL;
        for (int i = 0; i < 8; ++i)
        {
            childOctant[i] = NULL;
        }
        centerOfMass    = origin    = Point(0,0,0);
        mass  = 0;
        size  = 1;
        theta = 1;
    }

    Cell(double len, int x = 0, int y = 0, int z = 0, mac = 1)
    {
        singleParticle  = parent    = NULL;
        for (int i = 0; i < 8; ++i)
        {
            childOctant[i] = NULL;
        }
        centerOfMass    = origin    = Point(x,y,z);
        mass  = 0;
        size  = len;
        theta = mac;
    }

    Cell(double len, Point p, mac = 1)
    {
        singleParticle  = parent    = NULL;
        centerOfMass    = origin    = p;
        for (int i = 0; i < 8; ++i)
        {
            childOctant[i] = NULL;
        }
        mass = 0;
        size = len;
        theta = mac;
    }

    std::vector<Particle> particles;
    Particle* singleParticle;
    Cell* childOctant[8];
    Cell* parent;
    Point origin;
    Point centerOfMass;
    double mass;
    double size;
    double theta;

    Point getOrigin(int octant)
    {
        Point temp(origin);
        if(octant==0 || origin==3 || origin==4 || origin==7)
        {
            temp.x += size/2;
        }
        else
        {
            temp.x -= size/2;
        }

        if(octant==0 || origin==1 || origin==4 || origin==5)
        {
            temp.y += size/2;
        }
        else
        {
            temp.y -= size/2;
        }

        if(octant==0 || origin==1 || origin==2 || origin==3)
        {
            temp.z += size/2;
        }
        else
        {
            temp.z -= size/2;
        }
        return temp;
    }

    void insetToRoot(Particle newParticle)
    {
        int octant;
        Point newPoint = newParticle.getPosition();
        if(particles.size() > 1)
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
        else if(particles.size() == 1)
        {
            if(singleParticle->getPosition() != newParticle.getPosition())
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
                childOctant[octant]->insetToRoot(singleParticle());
                octant = newParticle.getPosition().getOctant(origin);
                if(octant < 0)
                {
                    octant = 0;
                }
                if(childOctant[octant] == NULL)
                {
                    childOctant[octant] = new Cell(size/2, this->getOrigin(octant));
                }
                childOctant[octant]->insetToRoot(newParticle());
            }
            else
            {
                ;
                //particle already present, update it??
                //implement collision?
                //aggregate it?
                //something like it?
            }
        }
        else if(particles.size() == 0)
        {
            singleParticle = new Particle(newParticle);
        }
        particles.push_back(newParticle);
    }

    void calcMassDistribution()
    {
        if(particles.size() == 1)
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
                mass += childOctant->mass;
                centerOfMass +=  childOctant[i]->mass * childOctant[i]->centerOfMass;
            }
            centerOfMass /= mass;
        }
    }

    Vector calcForce(Particle target)
    {
        Vector force = 0;
        if(particles.size() == 1)
        {
            force = G*target.getMass()*particles[0].getMass() * pow((target.getPosition()-particles[0].getPosition()).mod(), -2);
        }
        else
        {
            double r = (target.getPosition()-particles[0].getPosition()).mod();
            double d = size;
            if (d/r < _theta)
            {
              force = G*target.getMass()*mass * pow((target.getPosition()-centerOfMass).mod(), -2);
            }
            else
            {
                for(int i = 0; i < 8; ++i)
                {
                    if(childOctant[i] == NULL)
                    {
                        continue;
                    }
                    force += n.calcForce(target)
                }
            }
        }
        return force;
    }
};

#endif
// _CELL_H_