#ifndef __FuriousBlocksCore_H_
#define __FuriousBlocksCore_H_

#include <cstdint>
#include <set>
#include <unordered_map>
#include <memory>
#include "FuriousBlocksCoreListener.h"
#include "FuriousBlocksCoreDefaults.h"
#include "Player.h"
#include "Panel.h"

class FuriousBlocksCore : PanelListener {
private:
  int32_t seed;
  bool running;
  bool paused;
  bool singleTick;
  FuriousBlocksCoreListener* listener;

public:
  std::array<std::array<BlockType, FuriousBlocksCoreDefaults::PANEL_HEIGHT>, FuriousBlocksCoreDefaults::PANEL_WIDTH> initialBlockTypes;
  // BlockType initialBlockTypes[FuriousBlocksCoreDefaults::PANEL_WIDTH][FuriousBlocksCoreDefaults::PANEL_HEIGHT];
  std::unordered_map<Player*, Panel*> playerToPanel;

  FuriousBlocksCore(int32_t seed, FuriousBlocksCoreListener* listener = nullptr);
  ~FuriousBlocksCore();

  void addPlayer(Player* newPlayer);
  void addPlayer(Player* newPlayer, Panel* panel);
  void run();
  void pause();
  void resume();
  void stop();
  void onTick(int64_t tick);
  void onCombo(Combo* combo);
  void onEvent(int64_t playerId, PanelEvent panelEvent);
  void justATick();
  void onGameOver();
};

#endif //__FuriousBlocksCore_H_
