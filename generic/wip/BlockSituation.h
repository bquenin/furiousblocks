#ifndef __BlockSituation_H_
#define __BlockSituation_H_

#include <cstdint>
#include "BlockType.h"
#include "BlockState.h"

class BlockSituation {
private:
  int32_t stateTick;
  int32_t garbageOwner;
  bool combo;
  bool fallingFromClearing;
  int32_t poppingIndex;

protected:
public:
  int32_t id;
  BlockType type;
  BlockState state;
  bool movable;
  bool combinable;
  BlockSituation(int32_t id, BlockType type, BlockState state, int32_t stateTick, int32_t garbageBlockType, int32_t garbageOwner, bool combo, bool justLand, bool fallingFromClearing, int32_t poppingIndex, bool movable, bool combinable);
  static bool isComputable(BlockSituation *blockSituation);
  static bool isMovable(BlockSituation *blockSituation);
  int32_t getPoppingIndex();
  bool isFallingFromClearing();
  int32_t garbageBlockType;
  bool justLand;
};

#endif //__BlockSituation_H_
