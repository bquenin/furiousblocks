#ifndef __PanelSituation_H_
#define __PanelSituation_H_

#include <cstdint>
#include "GarbageSituation.h"
#include "BlockSituation.h"
#include "PanelState.h"
#include "PanelSituation.h"
#include "ComboSituation.h"
#include "Point.h"

using namespace std;

class PanelSituation {
private:
  BlockSituation ***blockSituations;
  bool locked = false;
  const unordered_set<ComboSituation *> &comboSituations;
  furiousblocks::Point& cursorPosition;
  int32_t scrollingOffset = 0;
  PanelState state;
  int32_t stateTick = 0;
  const unordered_set<GarbageSituation *> &garbageSituations;
  const unordered_set<GarbageSituation *> &garbageStackSituation;
  int32_t skillChainLevel = 0;
  int32_t freezingTime = 0;
  bool gameOver = false;
  int32_t wallOffset = 0;
  bool gracing = false;
  int32_t score = 0;
  bool clearing = false;

protected:
public:
  PanelSituation(BlockSituation ***blockSituations, bool locked, const unordered_set<ComboSituation *> & comboSituations, furiousblocks::Point& cursorPosition, int32_t scrollingOffset, PanelState state, int32_t stateTick, const unordered_set<GarbageSituation *> &garbages, const unordered_set<GarbageSituation *> & garbageStackSituation, int32_t skillChainLevel, int32_t freezingTime, bool gameOver, int32_t wallOffset, bool gracing, int32_t score, bool clearing);
  GarbageSituation* getGarbageByBlock(int32_t blockId);
  ComboSituation* getComboByBlock(int32_t blockId);
};

#endif //__PanelSituation_H_
