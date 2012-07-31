#include <cstdint>
#include "GarbageSituation.h"
#include "BlockSituation.h"
#include "PanelState.h"
#include "PanelSituation.h"

using namespace std;

PanelSituation::PanelSituation(unique_ptr<BlockSituation> blockSituations[FuriousBlocksCoreDefaults::PANEL_WIDTH][FuriousBlocksCoreDefaults::PANEL_HEIGHT+ 1], bool locked, const vector<ComboSituation > & comboSituations, furiousblocks::Point& cursorPosition, int32_t scrollingOffset, PanelState state, int32_t stateTick, const vector<GarbageSituation > &garbages, const vector<GarbageSituation > & garbageStackSituation, int32_t skillChainLevel, int32_t freezingTime, bool gameOver, int32_t wallOffset, bool gracing, int32_t score, bool clearing):
 locked(locked), comboSituations(comboSituations), cursorPosition(cursorPosition), scrollingOffset(scrollingOffset), state(state), stateTick(stateTick), garbageSituations(garbageSituations), garbageStackSituation(garbageStackSituation), skillChainLevel(skillChainLevel), freezingTime(freezingTime), gameOver(gameOver), wallOffset(wallOffset), gracing(gracing), score(score), clearing(clearing) {
 }

GarbageSituation PanelSituation::getGarbageByBlock(int32_t blockId) {
  for (auto garbageSituation: garbageSituations) {
    if (garbageSituation.contains(blockId)) {
      return garbageSituation;
    }
  }
}

ComboSituation PanelSituation::getComboByBlock(int32_t blockId) {
  for (auto comboSituation: comboSituations) {
    if (comboSituation.contains(blockId)) {
      return comboSituation;
    }
  }
}
