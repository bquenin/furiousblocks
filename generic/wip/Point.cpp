#include <cstdint>
#include "Point.h"

furiousblocks::Point::Point()
{
    Point(0, 0);
}

furiousblocks::Point::Point(Point* p)
{
    Point(p->x, p->y);
}

furiousblocks::Point::Point(int32_t x, int32_t y)
{
    this->x = x;
    this->y = y;
}
