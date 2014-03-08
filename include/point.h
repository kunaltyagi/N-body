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
        z = p.z;
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

    Point operator ^ (Point P) //cross product
    {
        return Point((y*P.z - z*P.y), (- x*P.z + z*P.x), (x*P.y - y*P.x));
    }

    double mod()
    {
        return sqrt(x*x + y*y + z*z);
    }
};
#endif
// _POINT_H_