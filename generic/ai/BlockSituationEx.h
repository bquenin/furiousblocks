#ifndef __BlockSituationEx_H_
#define __BlockSituationEx_H_

#include <cstdint>
#include <unordered_map>
#include <MacTypes.h>
#include "BlockSituation.h"

class BlockSituationEx : BlockSituation {
private:
  std::unordered_map<int32_t, int32_t> targetColumnCosts;
  Point *origin;
  bool chainReplacement;
  BlockSituationEx();

protected:
public:
  BlockSituationEx(BlockSituation *bs);
  BlockSituationEx(BlockSituationEx *bsEx);
  int32_t getTargetColumnCost(int32_t targetColumn);
  void addTargetCost(int32_t targetColumn, int32_t cost);
  void reset();
  static BlockSituationEx *newInvisibleBlock();
  bool isReplacement();
};

#endif //__BlockSituationEx_H_
