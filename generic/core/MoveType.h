#ifndef __MoveType_H_
#define __MoveType_H_

#include <cstdint>

enum class MoveType {
  CURSOR_UP,
  CURSOR_DOWN,
  CURSOR_LEFT,
  CURSOR_RIGHT,
  BLOCK_SWITCH,
  LIFT
};

#endif //__MoveType_H_
