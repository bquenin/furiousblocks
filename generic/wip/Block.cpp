#include "Block.h"

Block::Block(int id, BlockType type, int index, int skillChainLevel)
:id(0), type(nullptr), state(nullptr), stateTick(0), garbageBlockType(0), garbageOwner(0), poppingIndex(0), poppingSkillChainLevel(0), combo(false), fallingFromClearing(false), justLand(false), clearing(nullptr) {
  this->id = id;
  this->type = type;
  idle();
  fallingFromClearing = false;
  justLand = false;
  poppingIndex = index;
  poppingSkillChainLevel = skillChainLevel;
}

int Block::getId() {
  return id;
}

BlockType Block::getType() {
  return type;
}

BlockState Block::getState() {
  return state;
}

int Block::getStateTick() {
  return stateTick;
}

void Block::setGarbageOwner(int garbageOwner) {
  this->garbageOwner = garbageOwner;
}

bool Block::isFallingFromClearing() {
  return fallingFromClearing;
}

void Block::setFallingFromClearing(bool fallingFromClearing) {
  this->fallingFromClearing = fallingFromClearing;
}

void Block::setCombo() {
  this->combo = true;
}

int Block::getGarbageBlockType() {
  return garbageBlockType;
}

void Block::setGarbageBlockType(int garbageBlockType) {
  this->garbageBlockType = garbageBlockType;
}

int Block::getPoppingIndex() {
  return poppingIndex;
}

void Block::setPoppingIndex(int poppingIndex) {
  this->poppingIndex = poppingIndex;
}

int Block::getPoppingSkillChainLevel() {
  return poppingSkillChainLevel;
}

void Block::setPoppingSkillChainLevel(int poppingSkillChainLevel) {
  this->poppingSkillChainLevel = poppingSkillChainLevel;
}

void Block::setJustLand() {
  this->justLand = false;
}

bool Block::hasJustLand() {
  return justLand;
}

void Block::idle() {
  state = BlockState::IDLE;
  stateTick = 0;
  poppingIndex = 0;
  poppingSkillChainLevel = 0;
}

void Block::switchBack() {
  state = BlockState::SWITCHING_BACK;
  stateTick = FuriousBlocksCoreDefaults::BLOCK_SWITCHINGTIME;
}

void Block::switchForth() {
  state = BlockState::SWITCHING_FORTH;
  stateTick = FuriousBlocksCoreDefaults::BLOCK_SWITCHINGTIME;
}

void Block::hover() {
  state = BlockState::HOVERING;
  stateTick = FuriousBlocksCoreDefaults::BLOCK_HOVERINGTIME;
}

void Block::fall() {
  state = BlockState::FALLING;
  stateTick = 0;
}

void Block::land() {
  justLand = true;
  idle();
}

void Block::blink() {
  state = BlockState::BLINKING;
  stateTick = FuriousBlocksCoreDefaults::BLOCK_BLINKINGTIME;
}

void Block::explode(int explodingTime) {
  state = BlockState::EXPLODING;
  stateTick = explodingTime;
}

void Block::reveal(int revealingTime) {
  state = BlockState::REVEALING;
  stateTick = revealingTime;
}

void Block::airBounce() {
  state = BlockState::AIRBOUNCING;
  stateTick = FuriousBlocksCoreDefaults::BLOCK_AIRBOUNCINGTIME;
}

void Block:: delete() {
  state = BlockState::TO_DELETE;
}

PanelEvent *Block::update() {
  PanelEvent *event = nullptr;
  if (stateTick > 0) {
    stateTick--;
  }
  if (stateTick <= 0) {
    switch (state) {
      case BlockState::BLINKING:
        state = BlockState::DONE_BLINKING;
        break;
      case BlockState::SWITCHING_FORTH:
        state = BlockState::DONE_SWITCHING_FORTH;
        break;
      case BlockState::HOVERING:
        state = BlockState::DONE_HOVERING;
        break;
      case BlockState::EXPLODING:
        event = new PanelEvent(PanelEventType::BLOCK_POP);
        state = BlockState::DONE_EXPLODING;
        break;
      case BlockState::REVEALING:
        if (stateTick == 0) {
          event = new PanelEvent(PanelEventType::BLOCK_POP);
        }
        state = BlockState::DONE_REVEALING;
        break;
      case BlockState::AIRBOUNCING:
        state = BlockState::DONE_AIRBOUNCING;
        break;
      case BlockState::DONE_BLINKING:
      case BlockState::DONE_EXPLODING:
      case BlockState::DONE_REVEALING:
      case BlockState::DONE_SWITCHING_FORTH:
      case BlockState::DONE_HOVERING:
      case BlockState::IDLE:
      case BlockState::TO_DELETE:
      case BlockState::FALLING:
      case BlockState::SWITCHING_BACK:
      case BlockState::DONE_AIRBOUNCING:
        break;
      default:
        break;
    }
  }
  return event;
}

BlockSituation *Block::getSituation() {
  return new BlockSituation(id, type, state, stateTick, garbageBlockType, garbageOwner, combo, justLand, fallingFromClearing, poppingIndex);
}

bool Block::isComputable(Block *block) {
  return block != nullptr && block->movable && block->state == BlockState::IDLE;
}

void Block::setClearing(Clearing *clearing) {
  this->clearing = clearing;
}

Clearing *Block::getClearing() {
  return clearing;
}
