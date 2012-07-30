#include <cstdint>
#include <map>
#include "PanelSituation.h"
#include "GameSituation.h"

using namespace std;

GameSituation::GameSituation(map<int32_t, PanelSituation *> panelSituations) {
  playerIdToPanelSituation = panelSituations;
}

const map<int32_t, PanelSituation *> &GameSituation::getPlayerIdToPanelSituation() {
  return playerIdToPanelSituation;
}
