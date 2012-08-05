#ifndef __FuriousBlocksCore_H_
#define __FuriousBlocksCore_H_

#include <cstdint>
#include <set>
#include <map>
#include <atomic>
#include "FuriousBlocksCoreListener.h"
#include "FuriousBlocksCoreDefaults.h"
#include "Player.h"
#include "Panel.h"
#include "GameSituation.h"


class FuriousBlocksCore : PanelListener {
private:
  static constexpr int64_t nanoPeriod = static_cast<int64_t>((1.0f / FuriousBlocksCoreDefaults::CORE_FREQUENCY * 1000000000));
  int32_t seed;
  int64_t tick;
  volatile bool running;
  volatile bool paused;
  bool singleTick;
  FuriousBlocksCoreListener *listener;

protected:
  std::map<Player *, Panel *> playerToPanel;
  std::atomic<GameSituation *> gameSituation;

public:
  BlockType initialBlockTypes[FuriousBlocksCoreDefaults::PANEL_WIDTH][FuriousBlocksCoreDefaults::PANEL_HEIGHT];
  FuriousBlocksCore(int32_t seed, FuriousBlocksCoreListener *listener = nullptr);
  void addPlayer(Player *newPlayer);
  void addPlayer(Player *newPlayer, Panel *panel);
  void run();
  void pause();
  void resume();
  void stop();
  void onTick(int64_t tick);
  void onCombo(Combo *combo);
  void onEvent(int64_t playerId, PanelEvent *panelEvent);
  //  std::set<Player *> getPlayers();
  void justATick();
};

#endif //__FuriousBlocksCore_H_
