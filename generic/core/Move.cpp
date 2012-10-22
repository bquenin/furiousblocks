#include <cstdint>
#include "Move.h"

Move::Move(int8_t type)
:type(type) {
}

Move::Move(Move *move)
:type(move->type) {
}
