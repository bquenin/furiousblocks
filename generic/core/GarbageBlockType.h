#ifndef __GarbageBlockType_H_
#define __GarbageBlockType_H_

#include <cstdint>

class GarbageBlockType {
private:
protected:
public:
  static constexpr int32_t UPLEFTDOWN = 1;
  static constexpr int32_t UPDOWN = 2;
  static constexpr int32_t UPRIGHTDOWN = 3;
  static constexpr int32_t UPLEFT = 4;
  static constexpr int32_t UP = 5;
  static constexpr int32_t UPRIGHT = 6;
  static constexpr int32_t DOWNLEFT = 7;
  static constexpr int32_t DOWN = 8;
  static constexpr int32_t DOWNRIGHT = 9;
  static constexpr int32_t LEFT = 10;
  static constexpr int32_t PLAIN = 11;
  static constexpr int32_t RIGHT = 12;
};

#endif //__GarbageBlockType_H_
