#ifndef __GarbageBlockType_H_
#define __GarbageBlockType_H_

#include <cstdint>

class GarbageBlockType {
private:
protected:
public:
  int32_t UPLEFTDOWN = 1;
  int32_t UPDOWN = 2;
  int32_t UPRIGHTDOWN = 3;
  int32_t UPLEFT = 4;
  int32_t UP = 5;
  int32_t UPRIGHT = 6;
  int32_t DOWNLEFT = 7;
  int32_t DOWN = 8;
  int32_t DOWNRIGHT = 9;
  int32_t LEFT = 10;
  int32_t PLAIN = 11;
  int32_t RIGHT = 12;
};

#endif //__GarbageBlockType_H_
