#ifndef __MoveType_H_
#define __MoveType_H_

#include <cstdint>

class MoveType {
private:
protected:
public:
  static const int8_t CURSOR_UP = 1;
  static const int8_t CURSOR_DOWN = 2;
  static const int8_t CURSOR_LEFT = 3;
  static const int8_t CURSOR_RIGHT = 4;
  static const int8_t BLOCK_SWITCH = 5;
  static const int8_t LIFT = 6;
  static const int8_t HEARTBEAT = 127;
};

#endif //__MoveType_H_
