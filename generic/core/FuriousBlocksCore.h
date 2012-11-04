#ifndef __FuriousBlocksCore_H_
#define __FuriousBlocksCore_H_

#include <cstdint>
#include <set>
#include <unordered_map>
#include <atomic>
#include <memory>
#include "FuriousBlocksCoreListener.h"
#include "FuriousBlocksCoreDefaults.h"
#include "Player.h"
#include "Panel.h"

class FuriousBlocksCore : PanelListener {
private:
//  static constexpr int64_t nanoPeriod = static_cast<int64_t>((1.0f / FuriousBlocksCoreDefaults::CORE_FREQUENCY * 1000000000));
  int32_t seed;
  volatile bool running;
  volatile bool paused;
  bool singleTick;
  FuriousBlocksCoreListener *listener;

public:
  BlockType initialBlockTypes[FuriousBlocksCoreDefaults::PANEL_WIDTH][FuriousBlocksCoreDefaults::PANEL_HEIGHT];
  FuriousBlocksCore(int32_t seed, FuriousBlocksCoreListener *listener = nullptr);
  std::unordered_map<Player *, Panel *> playerToPanel;

  void addPlayer(Player *newPlayer);
  void addPlayer(Player *newPlayer, Panel *panel);
  void run();
  void pause();
  void resume();
  void stop();
  void onTick(int64_t tick);
  void onCombo(Combo *combo);
  void onEvent(int64_t playerId, PanelEvent panelEvent);
  void justATick();
  void onGameOver();
};

#endif //__FuriousBlocksCore_H_
