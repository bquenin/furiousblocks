#include <cstdint>
#include "BlockSituationEx.h"

BlockSituationEx::BlockSituationEx()
: BlockSituation(0, BlockType::INVISIBLE, BlockState::IDLE, 0, 0, 0, false, false, false, 0)
, origin(nullptr)
, chainReplacement(false) {
}

BlockSituationEx::BlockSituationEx(BlockSituation *bs)
: BlockSituation(bs->id, bs->type, bs->type, bs->stateTick, bs->garbageBlockType, bs->garbageOwner, bs->combo, bs->justLand, bs->fallingFromClearing, bs->poppingIndex)
, origin(nullptr)
, chainReplacement(false) {
}

BlockSituationEx::BlockSituationEx(BlockSituationEx *bsEx)
: BlockSituation(bsEx->id, bsEx->type, bsEx->type, bsEx->stateTick, bsEx->garbageBlockType, bsEx->garbageOwner, bsEx->combo, bsEx->justLand, bsEx->fallingFromClearing, bsEx->poppingIndex)
, origin(bsEx->origin)
, chainReplacement(bsEx->chainReplacement)
, targetColumnCosts(bsEx->targetColumnCosts) {
}

int32_t BlockSituationEx::getTargetColumnCost(int32_t targetColumn) {
  return targetColumnCosts[targetColumn];
}

void BlockSituationEx::addTargetCost(int32_t targetColumn, int32_t cost) {
  targetColumnCosts[targetColumn] = cost;
}

void BlockSituationEx::reset() {
  origin = nullptr;
  targetColumnCosts.clear();
  chainReplacement = false;
}

BlockSituationEx *BlockSituationEx::newInvisibleBlock() {
  return new BlockSituationEx();
}

bool BlockSituationEx::isReplacement() {
  return !targetColumnCosts.empty();
}
