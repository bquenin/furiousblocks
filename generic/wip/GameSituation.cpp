#include <cstdint>
#include <map>
#include "GameSituation.h"

GameSituation::GameSituation(std::map<int32_t, PanelSituation *> panelSituations)
: playerIdToPanelSituation(panelSituations) {
}

GameSituation::~GameSituation() {
  for (auto p = playerIdToPanelSituation.begin(); p != playerIdToPanelSituation.end(); ++p) {
    delete p->second;
  }
}
