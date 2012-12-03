#ifndef __Move_H_
#define __Move_H_

#include <cstdint>
#include "MoveType.h"
#include "cocos2d.h"

class Move {
public:

  Move(MoveType type);
  Move(Move *move);

  MoveType type;
};

struct MoveDeleter {
  void operator() (Move* p) {
    CCLOG("Calling delete for Move object...");
    delete p;
  }
};

#endif //__Move_H_
