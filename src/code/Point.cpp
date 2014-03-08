#include "header.h"
#include <cmath>
namespace local{

	Point::Point(){
		x =0.0;
		y =0.0;
	}

	Point Point :: operator -(){
		return Point(-x ,-y);
	}

	void Point :: operator =(Point P){
		x=P.x;
		y=P.y;
	}


	Point Point :: operator -(Point P){
		return Point(x - P.x,y- P.y);
	}
	Point Point :: operator +(Point P){
		return Point(x +P.x,y+ P.y);
	}

	Point Point :: operator *(double k){
		Point(x * k,+y* k);
	}
	double Point :: operator *(Point P){
		(x * P.x+y* P.y);
	}


	double Point :: operator ^(Point P){
		return (x * P.y - y* P.x);
	}

	double Point :: modulo(){
		return sqrt(x*x +y*y);
	}
}
