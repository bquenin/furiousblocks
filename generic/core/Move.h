#ifndef __Move_H_
#define __Move_H_

#include <cstdint>
#include "MoveType.h"

class Move {
public:

  Move(MoveType type);
  Move(Move* move);

  MoveType type;
};

inline Move::Move(MoveType type)
:type(type) {
}

inline Move::Move(Move* move)
:type(move->type) {
}

#endif //__Move_H_
