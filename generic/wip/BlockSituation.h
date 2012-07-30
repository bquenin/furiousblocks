#ifndef __BlockSituation_H_
#define __BlockSituation_H_

#include <cstdint>
#include "BlockType.h"
#include "BlockState.h"

using namespace std;

class BlockSituation {
private:
  BlockType type;
  BlockState state;
  int32_t id = 0;
  int32_t stateTick = 0;
  int32_t garbageBlockType = 0;
  int32_t garbageOwner;
  int32_t poppingIndex;
  bool combo = false;
  bool justLand = false;
  bool fallingFromClearing = false;
  bool movable = false;
  bool combinable = false;

protected:
public:
  BlockSituation(int32_t id, BlockType type, BlockState state, int32_t stateTick, int32_t garbageBlockType, int32_t garbageOwner, bool combo, bool justLand, bool fallingFromClearing, int32_t poppingIndex);
  static bool isComputable(BlockSituation* blockSituation);
  static bool isMovable(BlockSituation* blockSituation);
};

#endif //__BlockSituation_H_
