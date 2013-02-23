#ifndef __Move_H_
#define __Move_H_

#include <cstdint>
#include "MoveType.h"

class Move {
public:
  Move(MoveType type);

  MoveType type;
};

#endif //__Move_H_
