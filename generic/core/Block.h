#ifndef __Block_H_
#define __Block_H_

#include <cstdint>
#include <memory>
#include "BlockState.h"
#include "BlockType.h"
#include "PanelEvent.h"

namespace fb {

  class Block {
  public:
    Block(int32_t id, BlockType type);
    void idle();
    void switchBack();
    void switchForth();
    void hover();
    void fall();
    void land();
    void blink();
    void explode(int32_t explodingTime);
    void reveal(int32_t revealingTime);
    void airBounce();
    void toDelete();
    std::unique_ptr<PanelEvent> update();
    static bool isComputable(Block* block);

    int32_t id;
    BlockType type;
    BlockState state;
    int32_t stateTick;
    int32_t garbageBlockType;
    int32_t garbageOwner;
//    bool combo;
    bool fallingFromClearing;
    bool justLand;
    bool movable;
    bool combinable;
  };
}
#endif //__Block_H_
