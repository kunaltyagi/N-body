#ifndef _CELL_H_
#define _CELL_H_

#include <vector>

class Cell
{
private:

public:
    std::vector<Point> points;
    Point* singlePoint;
    Cell* childOctant[8];
    Cell* parent;
};

#endif
// _CELL_H_