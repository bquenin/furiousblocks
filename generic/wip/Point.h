#ifndef __Point_H_
#define __Point_H_

#include <cstdint>

using namespace std;

namespace furiousblocks {

  class Point {
  private:
  protected:
  public:
    int32_t x = 0;
    int32_t y = 0;
    Point();
    Point(Point& p);
    Point(int32_t x, int32_t y);
  };
}
#endif //__Point_H_
