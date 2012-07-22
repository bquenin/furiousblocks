#ifndef __BlockSituation_H_
#define __BlockSituation_H_

#include "BlockType.h"
#include "BlockState.h"

class BlockSituation {
public:
  BlockSituation(int id, BlockType type, BlockState state, int stateTick, int garbageBlockType, int garbageOwner, bool combo, bool justLand, bool fallingFromClearing, int poppingIndex);
  int getId();
  BlockType getType();
  BlockState getState();
  int getStateTick();
  int getGarbageBlockType();
  int getGarbageOwner();
  bool isCombo();
  bool hasJustLand();
  const static bool isComputable(BlockSituation *blockSituation);
  const static bool isMovable(BlockSituation *blockSituation);
  int getPoppingIndex();
  bool isFallingFromClearing();

protected:
private:
  int id;
  BlockType type;
  BlockState state;
  int stateTick;
  int garbageBlockType;
  int garbageOwner;
  bool combo;
  bool justLand;
  bool fallingFromClearing;
  int poppingIndex;
  bool movable;
  bool combinable;
};

#endif //__BlockSituation_H_
