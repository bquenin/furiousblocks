#include <cstdint>
#include "Point.h"

furiousblocks::Point::Point(Point *p)
: x(p->x)
, y(p->y) {
}

furiousblocks::Point::Point(int32_t x, int32_t y)
: x(x)
, y(y) {
}
