#ifndef __GameSituation_H_
#define __GameSituation_H_

#include <cstdint>
#include <map>
#include "PanelSituation.h"

class GameSituation
{
private:
    std::map<int32_t,PanelSituation*> playerIdToPanelSituation;

protected:
public:
    GameSituation(std::map<int32_t,PanelSituation*> panelSituations);
    std::map<int32_t,PanelSituation*> getPlayerIdToPanelSituation();
};

#endif //__GameSituation_H_
