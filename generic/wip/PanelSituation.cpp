#include <cstdint>
#include "GarbageSituation.h"
#include "BlockSituation.h"
#include "PanelState.h"
#include "PanelSituation.h"

using namespace std;

PanelSituation::PanelSituation(BlockSituation ***blockSituations, bool locked, const unordered_set<ComboSituation *> & comboSituations, furiousblocks::Point& cursorPosition, int32_t scrollingOffset, PanelState state, int32_t stateTick, const unordered_set<GarbageSituation *> &garbages, const unordered_set<GarbageSituation *> & garbageStackSituation, int32_t skillChainLevel, int32_t freezingTime, bool gameOver, int32_t wallOffset, bool gracing, int32_t score, bool clearing):
blockSituations(blockSituations), locked(locked), comboSituations(comboSituations), cursorPosition(cursorPosition), scrollingOffset(scrollingOffset), state(state), stateTick(stateTick), garbageSituations(garbageSituations), garbageStackSituation(garbageStackSituation), skillChainLevel(skillChainLevel), freezingTime(freezingTime), gameOver(gameOver), wallOffset(wallOffset), gracing(gracing), score(score), clearing(clearing) {
}

GarbageSituation *PanelSituation::getGarbageByBlock(int32_t blockId) {
  for (auto garbageSituation: garbageSituations) {
    if (garbageSituation->contains(blockId)) {
      return garbageSituation;
    }
  }
  return nullptr;
}

ComboSituation* PanelSituation::getComboByBlock(int32_t blockId) {
  for (auto comboSituation: comboSituations) {
    if (comboSituation->contains(blockId)) {
      return comboSituation;
    }
  }
  return nullptr;
}
