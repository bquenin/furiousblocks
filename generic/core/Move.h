#ifndef __Move_H_
#define __Move_H_

#include <cstdint>
#include "MoveType.h"

class Move {
private:
protected:
public:
  MoveType type;
  Move(MoveType type);
  Move(Move *move);
};

#endif //__Move_H_
