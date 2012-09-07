#ifndef __PanelSituation_H_
#define __PanelSituation_H_

#include <cstdint>
#include <set>
#include "ComboSituation.h"
#include "PanelState.h"
#include "GarbageSituation.h"
#include "BlockSituation.h"
#include "Point.h"
#include "FuriousBlocksCoreDefaults.h"

class PanelSituation {
private:
  bool isLocked;
  PanelState state;
  int32_t stateTick;
  std::set<ComboSituation *> comboSituations;
  std::set<GarbageSituation *> garbageSituations;
  std::set<GarbageSituation *> garbageStackSituation;
  int32_t skillChainLevel;
  int32_t freezingTime;
  bool gameOver;
  int32_t wallOffset;
  bool gracing;
  int32_t score;

protected:
public:
  BlockSituation ***blockSituations;
  bool clearing;
  PanelSituation(BlockSituation ***blockSituations, bool isLocked, std::set<ComboSituation *> comboSituations, furiousblocks::Point cursorPosition, int32_t scrollingOffset, PanelState state, int32_t stateTick, std::set<GarbageSituation *> garbageSituations, std::set<GarbageSituation *> garbageStackSituation, int32_t skillChainLevel, int32_t freezingTime, bool gameOver, int32_t wallOffset, bool gracing, int32_t score, bool clearing);
  ~PanelSituation();
  GarbageSituation *getGarbageByBlock(int32_t blockId);
  ComboSituation *getComboByBlock(int32_t blockId);
  int32_t scrollingOffset;
  furiousblocks::Point cursorPosition;
};

#endif //__PanelSituation_H_
