#include <cstdint>
#include <map>
#include "GameSituation.h"

GameSituation::GameSituation(std::map<int32_t,PanelSituation*> panelSituations)
{
    playerIdToPanelSituation = panelSituations;
}

std::map<int32_t,PanelSituation*> GameSituation::getPlayerIdToPanelSituation()
{
    return playerIdToPanelSituation;
}
