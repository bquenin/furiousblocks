#ifndef __BlockSituation_H_
#define __BlockSituation_H_

#include <cstdint>
#include "BlockType.h"
#include "BlockState.h"

class BlockSituation {
private:

protected:
  int32_t stateTick;
  int32_t garbageOwner;
  int32_t poppingIndex;
  bool combo;
  bool fallingFromClearing;
public:
  BlockType type;
  BlockState state;
  int32_t id;
  int32_t garbageBlockType;
  bool movable;
  bool combinable;
  bool justLand;
  BlockSituation(int32_t id, BlockType type, BlockState state, int32_t stateTick, int32_t garbageBlockType, int32_t garbageOwner, bool combo, bool justLand, bool fallingFromClearing, int32_t poppingIndex, bool movable, bool combinable);
  static bool isComputable(BlockSituation *blockSituation);
  static bool isMovable(BlockSituation *blockSituation);
};

#endif //__BlockSituation_H_
