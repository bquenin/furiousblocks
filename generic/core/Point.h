#ifndef __Point_H_
#define __Point_H_

#include <cstdint>

namespace furiousblocks {
  class Point {
  public:
    Point(int32_t x = 0, int32_t y = 0);

    int32_t x;
    int32_t y;
  };
}
#endif //__Point_H_
