#ifndef _POINT_H_
#define _POINT_H_

#include <cmath>

class Point
{
private:

public:
    double x, y, z;

    Point()
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }

    Point(double a, double b, double c)
    {
        x = a;
        y = b;
        z = c;
    }

    void add(Point P)
    {
        x += P.x;
        y += P.y;
        z += P.z;
    }

    Point operator -()
    {
        return Point(-x ,-y, -z);
    }

    void operator = (Point P)
    {
        x = P.x;
        y = P.y;
        z = P.z;
    }

    bool operator == (Point P)
    {
        if(x != P.x)
        {
            return x==P.x;
        }
        if(y != P.x)
        {
            return y==P.y;
        }
        if(z != P.x)
        {
            return z==P.z;
        }
        return true;
        //return x==P.x && y==P.y && z==P.z;
    }

    Point operator - (Point P)
    {
        return Point(x-P.x, y-P.y, z-P.z);
    }

    Point operator + (Point P)
    {
        return Point(x+P.x, y+P.y, z+P.z);
    }

    Point operator * (double k)
    {
        return Point(x*k, y*k, z*k);
    }

    double operator * (Point P)
    {
        return (x*P.x + y*P.y + z*P.z);
    }

    Point operator / (double k)
    {
        return Point(x/k, y/k, z/k);
    }

    Point operator ^ (Point P) //cross product
    {
        return Point((y*P.z - z*P.y), (- x*P.z + z*P.x), (x*P.y - y*P.x));
    }

    double mod()
    {
        return sqrt(x*x + y*y + z*z);
    }

    int getOctant(Point origin)
    {
        int octant;
        if(origin == Point(x, y, z))
        {
            octant = 0;
        }
        else
        {
            if(x >= origin.x)
            {
                if(y >= origin.y)
                {
                    if(z >= origin.z)
                    {
                        octant = 1;
                    }
                    else
                    {
                        octant = 5;
                    }
                }
                else
                {
                    if(z >= origin.z)
                    {
                        octant = 4;
                    }
                    else
                    {
                        octant = 8;
                    }
                }
            }
            else
            {
                if(y >= origin.y)
                {
                    if(z >= origin.z)
                    {
                        octant = 2;
                    }
                    else
                    {
                        octant = 6;
                    }
                }
                else
                {
                    if(z >= origin.z)
                    {
                        octant = 3;
                    }
                    else
                    {
                        octant = 7;
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
};
#endif
// _POINT_H_