#ifndef __GarbageBlockType_H_
#define __GarbageBlockType_H_

#include <cstdint>

enum class GarbageBlockType {
  UPLEFTDOWN = 1,
  UPDOWN = 2,
  UPRIGHTDOWN = 3,
  UPLEFT = 4,
  UP = 5,
  UPRIGHT = 6,
  DOWNLEFT = 7,
  DOWN = 8,
  DOWNRIGHT = 9,
  LEFT = 10,
  PLAIN = 11,
  RIGHT = 12
};

#endif //__GarbageBlockType_H_
