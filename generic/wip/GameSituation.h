#ifndef __GameSituation_H_
#define __GameSituation_H_

#include <cstdint>
#include <map>
#include "PanelSituation.h"

using namespace std;

class GameSituation {
private:
  map<int32_t, PanelSituation *> playerIdToPanelSituation;

protected:
public:
  GameSituation(map<int32_t, PanelSituation *> panelSituations);
  const map<int32_t, PanelSituation *> &getPlayerIdToPanelSituation();
};

#endif //__GameSituation_H_
