#ifndef _POINT_H_
#define _POINT_H_

class Point{
public:
    double x;
    double y;
    double z;

    Point();
    Point operator -(Point P);
    Point operator -();
    Point operator +(Point P);
    double operator *(Point P); //dot product
    double operator ^(Point P);	//cross product
    double operator *(double k);
    void operator =(Point P);

    Point cross(Point P);
    double dot(P);
    double getLength();

    double modulo();

};
#endif
