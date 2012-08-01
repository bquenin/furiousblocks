#include <cstdint>
#include "Move.h"

Move::Move(int8_t type) {
  this->type = type;
}

Move::Move(Move *move) {
  type = move->type;
}
