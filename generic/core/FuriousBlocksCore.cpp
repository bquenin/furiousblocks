#include <cstdint>
#include <memory>
#include "FuriousBlocksCore.h"

FuriousBlocksCore::FuriousBlocksCore(int32_t seed, FuriousBlocksCoreListener *listener)
: seed(seed)
, running(false)
, paused(false)
, singleTick(false)
, listener(listener) {
  SimpleRNG random(seed);
  for (int32_t y = 1; y < FuriousBlocksCoreDefaults::PANEL_HEIGHT; y++) {
    for (int32_t x = 0; x < FuriousBlocksCoreDefaults::PANEL_WIDTH; x++) {
      initialBlockTypes[x][y] = static_cast<BlockType>(-1);
    }
  }

  for (int32_t y = 0; y < 4; y++) {
    for (int32_t x = 0; x < FuriousBlocksCoreDefaults::PANEL_WIDTH; x++) {
      initialBlockTypes[x][y] = static_cast<BlockType>(random.nextInt() % Panel::numberOfRegularBlocks);
    }
  }
}

FuriousBlocksCore::~FuriousBlocksCore() {
  for (auto &entry: playerToPanel) {
    Player *player = entry.first;
    Panel *panel = entry.second;
    delete player;
    delete panel;
  }
}

void FuriousBlocksCore::addPlayer(Player *newPlayer) {
  addPlayer(newPlayer, nullptr);
}

void FuriousBlocksCore::addPlayer(Player *newPlayer, Panel *panel) {
  playerToPanel[newPlayer] = panel == nullptr ? new Panel(seed + newPlayer->id, newPlayer->id, initialBlockTypes, *this) : panel;
}

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
    Player *player = entry.first;
    Panel *panel = entry.second;
    if (panel->isGameOver()) {
      continue;
    }
    panel->submitMove(player->onMoveRequest(*panel));
    panel->onTick(tick);
  }
}

void FuriousBlocksCore::onCombo(Combo *combo) {
  listener->onCombo(combo);
//  for (const auto & entry: playerToPanel) {
//    Player *player = entry.first;
//    Panel *panel = entry.second;
//    if ((player->id != combo->owner) && !panel->isGameOver() && combo->skillChainLevel > 1) {
//      panel->stackGarbage(panel->newGarbage(FuriousBlocksCoreDefaults::PANEL_WIDTH, (combo->skillChainLevel - 1), combo->owner, true));
//    }
//  }
}

void FuriousBlocksCore::onEvent(int64_t playerId, PanelEvent panelEvent) {
  //  if (listener != nullptr) {
  //    listener->onEvent(playerId, panelEvent);
  //  }
}

void FuriousBlocksCore::onGameOver() {
  listener->onGameOver();
}


//std::set<Player *> FuriousBlocksCore::getPlayers() {
//  return playerToPanel->keySet();
//}

void FuriousBlocksCore::justATick() {
  pause();
  singleTick = true;
}
