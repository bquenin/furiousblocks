#ifndef __Panel_H_
#define __Panel_H_

#include <cstdint>
#include <set>
#include <vector>
#include <array>
#include <unordered_set>
#include "Block.h"
#include "Combo.h"
#include "FuriousBlocksCoreDefaults.h"
#include "SimpleRNG.h"
#include "BlockType.h"
#include "PanelListener.h"
#include "Move.h"
#include "Point.h"

class Clearing;
class Garbage;

class Panel {
public:
  static constexpr int32_t numberOfRegularBlocks = 5;
  static constexpr int32_t X = FuriousBlocksCoreDefaults::PANEL_WIDTH;
  static constexpr int32_t Y_DISPLAY = FuriousBlocksCoreDefaults::PANEL_HEIGHT;
  static constexpr int32_t Y = Panel::Y_DISPLAY + (Panel::Y_DISPLAY * 4);
  static constexpr int32_t INITIAL_SCROLLING_SPEED = FuriousBlocksCoreDefaults::CORE_FREQUENCY;
  static constexpr int64_t NEXT_LEVEL = FuriousBlocksCoreDefaults::CORE_FREQUENCY * 30;

  Panel(int32_t seed, int32_t playerId, std::array<std::array<BlockType, FuriousBlocksCoreDefaults::PANEL_HEIGHT>, FuriousBlocksCoreDefaults::PANEL_WIDTH> initialBlockTypes, PanelListener &panelListener);

  std::unique_ptr<fb::Block> newRandom(BlockType excludedType = static_cast<BlockType>(-1));
  std::unique_ptr<fb::Block> newBlock(BlockType blockType);
  Garbage* newGarbage(int32_t width, int32_t height, int32_t owner, bool skill);

  void processMove();
  void dropGarbages();
  void scrolling(int64_t tick);
  void gracePeriod();
  void freeze(int32_t freezingTime);
  void newLine();
  void mechanics(int64_t tick);
  std::shared_ptr<Combo> getComboByBlock(fb::Block* block);
  std::shared_ptr<Garbage> getGarbageByBlock(std::shared_ptr<fb::Block> block);
  std::shared_ptr<Clearing> getClearingByBlock(std::shared_ptr<fb::Block> block);
  std::shared_ptr<Combo> detectCombo();
  void processCombo(std::shared_ptr<Combo> combo);
  void reset();
  void setTransposedBlocks(std::vector<std::vector<BlockType>> & blockTypes);
  void onTick(int64_t tick);
  void stackGarbage(Garbage* garbage);
  void submitMove(std::unique_ptr<Move>&& move);

  SimpleRNG random;
  std::array<std::array<std::shared_ptr<fb::Block>, Panel::Y>, Panel::X> blocks;

  std::unordered_set<std::shared_ptr<Combo>> combos;
  std::unordered_set<std::shared_ptr<Garbage>> garbages;
  std::unordered_set<std::shared_ptr<Clearing>> clearings;
  std::unordered_set<Garbage*> garbageStack;

  uint32_t level;
  int32_t lastIndex;
  int64_t localTick;
  int32_t playerId;
  int32_t levelScrollingSpeed;
  int64_t scrollingSpeed;
  int32_t freezingTime;
  int32_t bonusFreezingTime;
  int32_t skillChainLevel;
  std::unique_ptr<Move> move;
  bool locked;
  bool lifting;
  bool gracing;
  bool scrollingEnabled;
  PanelListener &panelListener;
  furiousblocks::Point cursor;
  int32_t scrollingDelta;
  uint64_t score;
  bool gameOver;
};

#endif //__Panel_H_
