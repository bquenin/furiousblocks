#ifndef __FuriousBlocksCore_H_
#define __FuriousBlocksCore_H_

#include <cstdint>
#include <set>
#include <map>
#import "FuriousBlocksCoreListener.h"
#import "FuriousBlocksCoreDefaults.h"
#import "Player.h"
#import "Panel.h"
#import "GameSituation.h"

class FuriousBlocksCore {
private:
  int32_t seed = 0;
  int64_t nanoPeriod = static_cast<int64_t>((1.0f / FuriousBlocksCoreDefaults::CORE_FREQUENCY * 1000000000));
  int64_t tick = 0;
  bool running = false;
  bool paused = false;
  bool singleTick = false;
  FuriousBlocksCoreListener *listener = nullptr;

protected:
  std::map<Player *, Panel *> playerToPanel;
  //    AtomicReference<GameSituation*>* gameSituation = new AtomicReference<GameSituation*>();

public:
  BlockType *initialBlockTypes[FuriousBlocksCoreDefaults::PANEL_WIDTH][FuriousBlocksCoreDefaults::PANEL_HEIGHT];
  FuriousBlocksCore(int32_t seed);
  FuriousBlocksCore(int32_t seed, FuriousBlocksCoreListener *listener);
  void addPlayer(Player *newPlayer);
  void addPlayer(Player *newPlayer, Panel *panel);
  //    AtomicReference<GameSituation*> getGameSituation();
  void run();
  void pause();
  void resume();
  void stop();
  void onTick(int64_t tick);
  void onCombo(Combo *combo);
  void onEvent(int64_t playerId, PanelEvent *panelEvent);
  std::set<Player *> getPlayers();
  void justATick();
};

#endif //__FuriousBlocksCore_H_
