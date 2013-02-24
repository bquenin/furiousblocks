#include <cstdint>
#include "Block.h"
#include "FuriousBlocksCoreDefaults.h"

namespace fb {

  Block::Block(int32_t id, BlockType type)
  : id(id)
  , type(type)
  , state(BlockState::IDLE)
  , stateTick(0)
  , garbageBlockType()
  , garbageOwner(0)
//  , combo(false)
  , fallingFromClearing(false)
  , justLand(false)
  , movable(false)
  , combinable(false) {
    switch (type) {
      case BlockType::GARBAGE:
        movable = false;
        combinable = false;
        break;
      case BlockType::INVISIBLE:
        movable = true;
        combinable = false;
        break;
      default:
        movable = true;
        combinable = true;
        break;
    }
  }

  void Block::idle() {
    state = BlockState::IDLE;
    stateTick = 0;
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

  void Block::explode(int32_t explodingTime) {
    state = BlockState::EXPLODING;
    stateTick = explodingTime;
  }

  void Block::reveal(int32_t revealingTime) {
    state = BlockState::REVEALING;
    stateTick = revealingTime;
  }

  void Block::airBounce() {
    state = BlockState::AIRBOUNCING;
    stateTick = FuriousBlocksCoreDefaults::BLOCK_AIRBOUNCINGTIME;
  }

  void Block::toDelete() {
    state = BlockState::TO_DELETE;
  }

  std::unique_ptr<PanelEvent> Block::update() {
    std::unique_ptr<PanelEvent> event(nullptr);
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
          event.reset(new PanelEvent(PanelEventType::BLOCK_POP));
          state = BlockState::DONE_EXPLODING;
          break;
        case BlockState::REVEALING:
          if (stateTick == 0) {
            event.reset(new PanelEvent(PanelEventType::BLOCK_POP));
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

  bool Block::isComputable(Block* block) {
    return block != nullptr && block->state == BlockState::IDLE && block->movable;
  }

  bool Block::isMovable(Block* block) {
    return block == nullptr || (block->state == BlockState::IDLE && block->movable);
  }

}
