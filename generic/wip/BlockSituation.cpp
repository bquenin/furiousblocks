#include "BlockSituation.h"

BlockSituation::BlockSituation(int id, BlockType type, BlockState state, int stateTick, int garbageBlockType, int garbageOwner, bool combo, bool justLand, bool fallingFromClearing, int poppingIndex)
:id(0), type(nullptr), state(nullptr), stateTick(0), garbageBlockType(0), garbageOwner(0), combo(false), justLand(false), fallingFromClearing(false), poppingIndex(0) {
  this->id = id;
  this->type = type;
  this->state = state;
  this->stateTick = stateTick;
  this->garbageBlockType = garbageBlockType;
  this->garbageOwner = garbageOwner;
  this->combo = combo;
  this->justLand = justLand;
  this->fallingFromClearing = fallingFromClearing;
  this->poppingIndex = poppingIndex;
}

int BlockSituation::getId() {
  return id;
}

BlockType BlockSituation::getType() {
  return type;
}

BlockState BlockSituation::getState() {
  return state;
}

int BlockSituation::getStateTick() {
  return stateTick;
}

int BlockSituation::getGarbageBlockType() {
  return garbageBlockType;
}

int BlockSituation::getGarbageOwner() {
  return garbageOwner;
}

bool BlockSituation::isCombo() {
  return combo;
}

bool BlockSituation::hasJustLand() {
  return justLand;
}

const static bool BlockSituation::isComputable(BlockSituation *blockSituation) {
  return (blockSituation != nullptr) && blockSituation->movable;
}

const static bool BlockSituation::isMovable(BlockSituation *blockSituation) {
  return (blockSituation == nullptr) || ((blockSituation->getState() == BlockState::IDLE) && (blockSituation->getType() != BlockType::GARBAGE));
}

int BlockSituation::getPoppingIndex() {
  return poppingIndex;
}

bool BlockSituation::isFallingFromClearing() {
  return fallingFromClearing;
}
