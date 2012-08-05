#include <cstdint>
#include "PanelSituation.h"

PanelSituation::PanelSituation(BlockSituation ***blockSituations, bool isLocked, std::set<ComboSituation *> comboSituations, furiousblocks::Point *cursorPosition, int32_t scrollingOffset, PanelState state, int32_t stateTick, std::set<GarbageSituation *> garbageSituations, std::set<GarbageSituation *> garbageStackSituation, int32_t skillChainLevel, int32_t freezingTime, bool gameOver, int32_t wallOffset, bool gracing, int32_t score, bool clearing)
: blockSituations(blockSituations), isLocked(isLocked), comboSituations(comboSituations), state(state), stateTick(stateTick), garbageSituations(garbageSituations),
garbageStackSituation(garbageStackSituation), skillChainLevel(skillChainLevel), cursorPosition(cursorPosition), scrollingOffset(scrollingOffset), freezingTime(freezingTime),
gameOver(gameOver), wallOffset(wallOffset), gracing(gracing), score(score), clearing(clearing) {
}

GarbageSituation *PanelSituation::getGarbageByBlock(int32_t blockId) {
  for (auto garbageSituation: garbageSituations) {
    if (garbageSituation->contains(blockId)) {
      return garbageSituation;
    }
  }
  return nullptr;
}

ComboSituation *PanelSituation::getComboByBlock(int32_t blockId) {
  for (auto comboSituation: comboSituations) {
    if (comboSituation->contains(blockId)) {
      return comboSituation;
    }
  }
  return nullptr;
}
