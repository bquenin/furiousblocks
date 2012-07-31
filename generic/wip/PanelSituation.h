#ifndef __PanelSituation_H_
#define __PanelSituation_H_

#include <cstdint>
#include <set>
#include "ComboSituation.h"
#include "PanelState.h"
#include "GarbageSituation.h"
#include "BlockSituation.h"
#include "Point.h"

class PanelSituation {
private:
  bool isLocked = false;
  furiousblocks::Point *cursorPosition = nullptr;
  int32_t scrollingOffset = 0;
  PanelState state;
  int32_t stateTick = 0;
  std::set<ComboSituation *> comboSituations;
  std::set<GarbageSituation *> garbageSituations;
  std::set<GarbageSituation *> garbageStackSituation;
  int32_t skillChainLevel = 0;
  int32_t freezingTime = 0;
  bool gameOver = false;
  int32_t wallOffset = 0;
  bool gracing = false;
  int32_t score = 0;

protected:
public:
  BlockSituation ***blockSituations = nullptr;
  bool clearing = false;
  PanelSituation(BlockSituation ***blockSituations, bool isLocked, std::set<ComboSituation *> comboSituations, furiousblocks::Point *cursorPosition, int32_t scrollingOffset, PanelState state, int32_t stateTick, std::set<GarbageSituation *> garbageSituations, std::set<GarbageSituation *> garbageStackSituation, int32_t skillChainLevel, int32_t freezingTime, bool gameOver, int32_t wallOffset, bool gracing, int32_t score, bool clearing);
  GarbageSituation *getGarbageByBlock(int32_t blockId);
  ComboSituation *getComboByBlock(int32_t blockId);
  PanelSituation *getSimpleClone();
};

#endif //__PanelSituation_H_
