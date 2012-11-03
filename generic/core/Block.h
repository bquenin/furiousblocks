#ifndef __Block_H_
#define __Block_H_

#include <cstdint>
#include <memory>
#include "BlockState.h"
#include "BlockType.h"
#include "PanelEvent.h"

class Block {
private:

protected:
public:
  int32_t id;
  BlockType type;
  BlockState state;
  int32_t stateTick;
  int32_t garbageBlockType;
  int32_t garbageOwner;
  int32_t poppingIndex;
  int32_t poppingSkillChainLevel;
  bool combo;
  bool fallingFromClearing;
  bool justLand;
  bool movable;
  bool combinable;
  void *clearing;
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
  static bool isComputable(Block *block);
  Block(int32_t id, BlockType type, int32_t index, int32_t skillChainLevel);
};

#endif //__Block_H_
