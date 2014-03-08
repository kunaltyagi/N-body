#ifndef _CELL_H_
#define _CELL_H_

#include <vector>

class Cell
{
private:

public:
    std::vector<Particle> particles;
    Particle* singleParticle;
    Cell* childOctant[8];
    Cell* parent;
    Point origin;

    int getOctant(Point p)
    {
        if(origin == p)
        {
            return 0;
        }
        else
        {
            if(p.x >= origin.x)
            {
                if(p.y >= origin.y)
                {
                    if(p.z >= origin.z)
                    {
                        return 1;
                    }
                    else
                    {
                        return 5;
                    }
                }
                else
                {
                    if(p.z >= origin.z)
                    {
                        return 4;
                    }
                    else
                    {
                        return 8;
                    }
                }
            }
            else
            {
                if(p.y >= origin.y)
                {
                    if(p.z >= origin.z)
                    {
                        return 2;
                    }
                    else
                    {
                        return 6;
                    }
                }
                else
                {
                    if(p.z >= origin.z)
                    {
                        return 3;
                    }
                    else
                    {
                        return 7;
                    }
                }
            }
        }
    }

    void insetToRoot(Particle newParticle)
    {
        int octant;
        if(particles.size() > 1)
        {
            octant = getOctant(newParticle.getPosition());
            octant -= 1;
            if(octant < 0)
            {
                octant = 0;
            }
            if(childOctant[octant] == NULL)
            {
                childOctant[octant] = new Cell;
            }
            childOctant[octant]->insetToRoot(newParticle);
        }
        else if(particles.size() == 1)
        {
            if(singleParticle->getPosition() != newParticle.getPosition())
            {
                octant = getOctant(singleParticle->getPosition());
                octant -= 1;
                if(octant < 0)
                {
                    octant = 0;
                }
                if(childOctant[octant] == NULL)
                {
                    childOctant[octant] = new Cell;
                }
                childOctant[octant]->insetToRoot(singleParticle());

                octant = getOctant(newParticle.getPosition());
                octant -= 1;
                if(octant < 0)
                {
                    octant = 0;
                }
                if(childOctant[octant] == NULL)
                {
                    childOctant[octant] = new Cell;
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
};

#endif
// _CELL_H_