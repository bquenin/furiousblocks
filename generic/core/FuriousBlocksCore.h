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
  std::unique_ptr<FuriousBlocksCoreListener> listener;

public:
  std::array<std::array<BlockType, FuriousBlocksCoreDefaults::PANEL_HEIGHT>, FuriousBlocksCoreDefaults::PANEL_WIDTH> initialBlockTypes;

  /// Long story short: You cannot use abstract classes in containers (it just doesn't compile).
  /// You can't use std::unique<T> if T is an abstract class.
  std::unordered_map<Player*, std::unique_ptr<Panel>> playerToPanel;

  FuriousBlocksCore(int32_t seed, std::unique_ptr<FuriousBlocksCoreListener>&& listener);
  ~FuriousBlocksCore();

  void addPlayer(Player* newPlayer);
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
