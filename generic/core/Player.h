#ifndef __Player_H_
#define __Player_H_

#include <cstdint>
#include <string>
#include "Move.h"
#include "Panel.h"


class Player {
public:
  Player() : id(simpleRNG.nextInt()) {};
  virtual std::unique_ptr<Move> onMoveRequest(const Panel &panel) = 0;

  virtual ~Player() {};

  int32_t id;
  SimpleRNG simpleRNG;
};

#endif //__Player_H_
