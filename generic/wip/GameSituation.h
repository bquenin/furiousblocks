#ifndef __GameSituation_H_
#define __GameSituation_H_

#include <cstdint>
#include <unordered_map>
#include "PanelSituation.h"

class GameSituation {
public:
  std::unordered_map<int32_t, PanelSituation *> playerIdToPanelSituation;
  GameSituation(std::unordered_map<int32_t, PanelSituation *> panelSituations);
  ~GameSituation();
};

#endif //__GameSituation_H_
