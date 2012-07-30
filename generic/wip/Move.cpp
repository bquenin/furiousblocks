#include <cstdint>
#include "Move.h"

using namespace std;

Move::Move(int8_t type) {
  this->type = type;
}

Move::Move(Move& move) {
  type = move.type;
}

int8_t Move::getType() {
  return type;
}
