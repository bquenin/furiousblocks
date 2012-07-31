#ifndef __Block_H_
#define __Block_H_

#include <cstdint>
#include "BlockState.h"
#include "BlockType.h"
#include "PanelEvent.h"
#include "BlockSituation.h"

class Clearing;

class Block
{
private:
    Clearing* clearing = nullptr;

protected:
public:
    int32_t id = 0;
    BlockType type;
    BlockState state;
    int32_t stateTick = 0;
    int32_t garbageBlockType = 0;
    int32_t garbageOwner = 0;
    int32_t poppingIndex = 0;
    int32_t poppingSkillChainLevel = 0;
    bool combo = false;
    bool fallingFromClearing = false;
    bool justLand = false;
    bool movable = false;
    bool combinable = false;
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
    PanelEvent* update();
    BlockSituation* getSituation();
    static bool isComputable(Block* block);
    void setClearing(Clearing* clearing);
    Clearing* getClearing();
  Block(int32_t id, BlockType type, int32_t index, int32_t skillChainLevel);
};

#endif //__Block_H_
