#include <cstdint>
#include <map>
#include "GameSituation.h"

GameSituation::GameSituation(std::map<int32_t, PanelSituation *> panelSituations)
: playerIdToPanelSituation(panelSituations) {
}
