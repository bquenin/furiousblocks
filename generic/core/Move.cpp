#include "Move.h"

Move::Move(MoveType type)
:type(type) {
}

Move::Move(Move&& move)
:type(type) {
}
