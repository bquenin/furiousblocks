#include <cstdint>
#include "BlockSituation.h"

using namespace std;

BlockSituation::BlockSituation(int32_t id, BlockType type, BlockState state, int32_t stateTick, int32_t garbageBlockType, int32_t garbageOwner, bool combo, bool justLand, bool fallingFromClearing, int32_t poppingIndex) :
id(id), type(type), state(state), stateTick(stateTick), garbageBlockType(garbageBlockType), garbageOwner(garbageOwner), combo(combo), justLand(justLand), fallingFromClearing(fallingFromClearing), poppingIndex(poppingIndex) {
}

bool BlockSituation::isComputable(BlockSituation* blockSituation) {
  return blockSituation != nullptr && blockSituation->movable;
}

bool BlockSituation::isMovable(BlockSituation* blockSituation) {
  return blockSituation != nullptr && blockSituation->state == BlockState::IDLE && blockSituation->type != BlockType::GARBAGE;
}
