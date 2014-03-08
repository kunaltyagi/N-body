#ifndef _CELL_H_
#define _CELL_H_

#include <vector>

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
        mass = 0;
    }

    std::vector<Particle> particles;
    Particle* singleParticle;
    Cell* childOctant[8];
    Cell* parent;
    Point origin;
    Point centerOfMass;
    double mass;

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
        if(octant == 0)
        {
            return 0;
        }
        else
        {
            return octant-1;
        }
    }

    void insetToRoot(Particle newParticle)
    {
        int octant;
        if(particles.size() > 1)
        {
            octant = getOctant(newParticle.getPosition());
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

    void calcForce()
    {
        ;
    }
Function force = TreeNode::CalculateForce(targetParticle)
  force = 0
  if number of particle equals 1
    force = Gravitational force between targetParticle and particle
  else
    r = distance from nodes center of mass to targetParticle
    d = height of the node
    if (d/r < θ)
      force = Gravitational force between targetParticle and node using the nodes center of mass and the total mass of the node
    else
      for all child nodes n
        force += n.CalculateForce(particle)
      end for
    end if
  end
end
};

#endif
// _CELL_H_