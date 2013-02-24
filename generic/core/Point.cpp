#include <cstdint>
#include "Point.h"

namespace fb {
  Point::Point(int32_t x, int32_t y)
  : x(x)
  , y(y) {
  }

  Point& Point::operator = (const Point& other) {
    if (this != &other) {
      x = other.x;
      y = other.y;
    }
    return *this;
  }

  bool Point::operator ==(const Point& other) const {
    return x == other.x && y == other.y;
  }
}
