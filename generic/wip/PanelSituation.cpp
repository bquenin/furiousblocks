#include <cstdint>
#include <iostream>
#include "PanelSituation.h"

PanelSituation::PanelSituation(BlockSituation ***blockSituations, bool isLocked, std::set<ComboSituation *> comboSituations, furiousblocks::Point cursorPosition, int32_t scrollingOffset, PanelState state, int32_t stateTick, std::set<GarbageSituation *> garbageSituations, std::set<GarbageSituation *> garbageStackSituation, int32_t skillChainLevel, int32_t freezingTime, bool gameOver, int32_t wallOffset, bool gracing, int32_t score, bool clearing)
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

PanelSituation::~PanelSituation() {
  for (auto i = comboSituations.begin(); i != comboSituations.end(); ++i) {
    delete *i;
  }
  for (auto i = garbageSituations.begin(); i != garbageSituations.end(); ++i) {
    delete *i;
  }
  for (auto i = garbageStackSituation.begin(); i != garbageStackSituation.end(); ++i) {
    delete *i;
  }

  // BlockSituations deletion
  for (int x = 0; x < FuriousBlocksCoreDefaults::PANEL_WIDTH; x++) {
    for (int y = 0; y < FuriousBlocksCoreDefaults::PANEL_HEIGHT + 1; y++) {
      if (blockSituations[x][y] != NULL) {
        delete blockSituations[x][y];
      }
    }
  }
  for (int x = 0; x < FuriousBlocksCoreDefaults::PANEL_WIDTH; x++) {
    delete[] blockSituations[x];
  }
  delete[] blockSituations;
}
