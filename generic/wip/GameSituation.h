#ifndef __GameSituation_H_
#define __GameSituation_H_

#include <cstdint>
#include <map>
#include "PanelSituation.h"

class GameSituation {
public:
  std::map<int32_t, PanelSituation *> playerIdToPanelSituation;
  GameSituation(std::map<int32_t, PanelSituation *> panelSituations);
};

#endif //__GameSituation_H_
