#include "GameSituation.h"
using namespace std;

GameSituation::GameSituation(map<Integer*,PanelSituation*>* panelSituations)
:playerIdToPanelSituation(nullptr)
{
    playerIdToPanelSituation = panelSituations;
}

map<Integer*,PanelSituation*> GameSituation::getPlayerIdToPanelSituation()
{
    return Collections->unmodifiableMap(playerIdToPanelSituation);
}
