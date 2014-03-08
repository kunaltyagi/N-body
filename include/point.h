#include "header.h"
#include <cmath>


class Point
{
private:
    double x, y, z;
public:
    Point()
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
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
        Point(x*k, y*k, z*k);
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