#ifndef __PanelSituation_H_
#define __PanelSituation_H_

#include <cstdint>
#include <vector>
#include "GarbageSituation.h"
#include "BlockSituation.h"
#include "PanelState.h"
#include "PanelSituation.h"
#include "ComboSituation.h"
#include "Point.h"
#include "FuriousBlocksCoreDefaults.h"

using namespace std;

class PanelSituation {
private:
  unique_ptr<BlockSituation> blockSituations[FuriousBlocksCoreDefaults::PANEL_WIDTH][FuriousBlocksCoreDefaults::PANEL_HEIGHT+ 1];
  bool locked = false;
  const vector<ComboSituation> &comboSituations;
  furiousblocks::Point& cursorPosition;
  int32_t scrollingOffset = 0;
  PanelState state;
  int32_t stateTick = 0;
  const vector<GarbageSituation > &garbageSituations;
  const vector<GarbageSituation > &garbageStackSituation;
  int32_t skillChainLevel = 0;
  int32_t freezingTime = 0;
  bool gameOver = false;
  int32_t wallOffset = 0;
  bool gracing = false;
  int32_t score = 0;
  bool clearing = false;

protected:
public:
  PanelSituation(unique_ptr<BlockSituation> blockSituations[FuriousBlocksCoreDefaults::PANEL_WIDTH][FuriousBlocksCoreDefaults::PANEL_HEIGHT+ 1], bool locked, const vector<ComboSituation > & comboSituations, furiousblocks::Point& cursorPosition, int32_t scrollingOffset, PanelState state, int32_t stateTick, const vector<GarbageSituation > &garbages, const vector<GarbageSituation > & garbageStackSituation, int32_t skillChainLevel, int32_t freezingTime, bool gameOver, int32_t wallOffset, bool gracing, int32_t score, bool clearing);
  GarbageSituation getGarbageByBlock(int32_t blockId);
  ComboSituation getComboByBlock(int32_t blockId);
};

#endif //__PanelSituation_H_
