#ifndef __FuriousBlocksCore_H_
#define __FuriousBlocksCore_H_

#include <cstdint>
#include <set>
#include <map>
#include "FuriousBlocksCoreListener.h"
#include "Panel.h"
#include "PanelSituation.h"
#include "Player.h"
#include "SimpleRNG.h"
#include "GameSituation.h"
#include "Move.h"
#include "BlockType.h"
#include "NetworkContext.h"
#include "PanelEvent.h"

using namespace std;

class FuriousBlocksCore {
private:
  int32_t seed = 0;
  int64_t nanoPeriod = static_cast<int64_t>((1f / FuriousBlocksCoreDefaults::CORE_FREQUENCY * 1000000000));
  int64_t tick = 0;
  bool running = false;
  bool paused = false;
  bool singleTick = false;
  FuriousBlocksCoreListener& listener = nullptr;

protected:
  map<Player *, Panel *> playerToPanel;
  AtomicReference<GameSituation *>& gameSituation = new AtomicReference<GameSituation *>();
  map<int32_t, NetworkContext *> networkContexts;

public:
  BlockType *initialBlockTypes[FuriousBlocksCoreDefaults::PANEL_WIDTH][FuriousBlocksCoreDefaults::PANEL_HEIGHT] = nullptr;
  FuriousBlocksCore(int32_t seed);
  FuriousBlocksCore(int32_t seed, FuriousBlocksCoreListener& listener);
  void addPlayer(Player& newPlayer);
  void addPlayer(Player& newPlayer, Panel& panel);
  AtomicReference<GameSituation *> getGameSituation();
  void run();
  void pause();
  void resume();
  void stop();
  void onTick(int64_t tick);
  void onEvent(int64_t playerId, PanelEvent* panelEvent);
  set<Player *> getPlayers();
  void justATick();
};

#endif //__FuriousBlocksCore_H_
