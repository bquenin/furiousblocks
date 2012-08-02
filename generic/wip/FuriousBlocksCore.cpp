#include <cstdint>
#include <set>
#include <map>
#include "FuriousBlocksCore.h"

FuriousBlocksCore::FuriousBlocksCore(int32_t seed, FuriousBlocksCoreListener *listener) {
  this->listener = listener;
  this->seed = seed;
  SimpleRNG *random = new SimpleRNG(seed);
  for (int32_t y = 0; y < 4; y++) {
    for (int32_t x = 0; x < FuriousBlocksCoreDefaults::PANEL_WIDTH; x++) {
      initialBlockTypes[x][y] = static_cast<BlockType >(random->nextInt() % Panel::numberOfRegularBlocks);
    }
  }
}

void FuriousBlocksCore::addPlayer(Player *newPlayer) {
  addPlayer(newPlayer, nullptr);
}

void FuriousBlocksCore::addPlayer(Player *newPlayer, Panel *panel) {
  playerToPanel[newPlayer] = panel == nullptr ? new Panel(seed + newPlayer->id, newPlayer->id, initialBlockTypes, this) : panel;
}

//AtomicReference<GameSituation *> FuriousBlocksCore::getGameSituation() {
//  return gameSituation;
//}

void FuriousBlocksCore::run() {
  running = true;
}

void FuriousBlocksCore::pause() {
  paused = true;
}

void FuriousBlocksCore::resume() {
  paused = false;
}

void FuriousBlocksCore::stop() {
  running = false;
}

void FuriousBlocksCore::onTick(int64_t tick) {
  for (const auto &entry: playerToPanel) {
//    Player *player = entry.first;
    Panel *panel = entry.second;
    if (panel->isGameOver()) {
      continue;
    }
//    Move *move = player->onMoveRequest();
//    if (move != nullptr) {
//      panel->submitMove(move);
//    }
  }

  std::map<int32_t, PanelSituation *> panelSituations;
  for (const auto &entry: playerToPanel) {
    Player *player = entry.first;
    Panel *panel = entry.second;
    PanelSituation *panelSituation = panel->onTick(tick);
    panelSituations[player->id] = panelSituation;
    if (panel->isGameOver()) {
      continue;
    }
    player->onSituationUpdate(panelSituation);
  }
  GameSituation * oldSituation = new GameSituation(panelSituations);
  if (oldSituation != nullptr) {
    delete oldSituation;
  }
}

void FuriousBlocksCore::onCombo(Combo *combo) {
  for (const auto & entry: playerToPanel) {
    Player *player = entry.first;
    Panel *panel = entry.second;
    if ((player->id != combo->owner) && !panel->isGameOver()) {
      if (combo->skillChainLevel > 1) {
        panel->stackGarbage(panel->newGarbage(FuriousBlocksCoreDefaults::PANEL_WIDTH, (combo->skillChainLevel - 1), combo->owner, true));
      }
    }
  }
}

void FuriousBlocksCore::onEvent(int64_t playerId, PanelEvent *panelEvent) {
  if (listener != nullptr) {
    listener->onEvent(playerId, panelEvent);
  }
}

//std::set<Player *> FuriousBlocksCore::getPlayers() {
//  return playerToPanel->keySet();
//}

void FuriousBlocksCore::justATick() {
  pause();
  singleTick = true;
}
