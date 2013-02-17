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

class Panel {
public:
  class Clearing;

private:


  class BlockBar {
    friend class Clearing;
    friend class Garbage;
    friend class BlockLine;

  protected:
    int32_t id;
    Panel* __parent;
    BlockBar(Panel* __parent, int32_t width, int32_t height, int32_t owner);
    int32_t owner;
  public:
    virtual void onDoneRevealing() = 0;
    bool contains(std::shared_ptr<fb::Block> block);
    bool hasToFall(int32_t xOrigin, int32_t yOrigin);
    void fall(int32_t xOrigin, int32_t yOrigin);
    void idle();
    void blink();
    bool isRevealing();
    int32_t width;
    int32_t height;
    std::unordered_set<std::shared_ptr<fb::Block>> barBlocks;
  };

  class Garbage : public BlockBar {
    friend class Clearing;
    friend class Panel;

  private:
    bool skill;
    std::shared_ptr<Combo> triggeringCombo;
    Panel* __parent;
    Garbage(Panel* __parent, int32_t width, int32_t height, int32_t owner, bool skill);
    void inject(int32_t x, int32_t y);
    void onDoneRevealing();

  protected:
  public:
    bool isSkill();
    int32_t getOwner();
    void blink(std::shared_ptr<Combo> combo);
    int32_t reveal(int32_t xOrigin, int32_t yOrigin, int32_t revealingTime, Clearing* parentClearing);
//    GarbageSituation *getSituation();
  };

  class BlockLine : public BlockBar {
  private:
    Panel* __parent;

    void onDoneRevealing();
  protected:
  public:
    BlockLine(Panel* __parent, int32_t width, int32_t owner);
    int32_t reveal(int32_t xOrigin, int32_t yOrigin, int32_t revealingTime);
    void inject(int32_t x, int32_t y);
  };

  static const int32_t INITIAL_SCROLLING_SPEED = static_cast<int32_t>(FuriousBlocksCoreDefaults::CORE_FREQUENCY);
  static const int64_t NEXT_LEVEL = static_cast<int64_t>((FuriousBlocksCoreDefaults::CORE_FREQUENCY * 30));
  int32_t lastIndex;
  SimpleRNG random;
  int64_t localTick;
  int32_t playerId;
  std::set<std::shared_ptr<Combo>> combos;
  std::set<std::shared_ptr<Panel::Garbage>> garbages;
  std::set<Clearing*> clearings;
  std::set<Panel::Garbage*> garbageStack;
  int32_t levelScrollingSpeed;
  int64_t scrollingSpeed;
  int32_t freezingTime;
  int32_t bonusFreezingTime;
  int32_t skillChainLevel;
  std::unique_ptr<Move, MoveDeleter> move;
  bool locked;
  bool lifting;
  bool gracing;
  PanelListener &panelListener;
  void processMove();
  void dropGarbages();
  void scrolling(int64_t tick);
  void gracePeriod();
  void freeze(int32_t freezingTime);
  void newLine();
  void mechanics(int64_t tick);
  std::shared_ptr<Combo> getComboByBlock(fb::Block* block);
  std::shared_ptr<Panel::Garbage> getGarbageByBlock(std::shared_ptr<fb::Block> block);
  std::shared_ptr<Combo> detectCombo();
  void processCombo(std::shared_ptr<Combo> combo);

protected:
  static const int32_t X = FuriousBlocksCoreDefaults::PANEL_WIDTH;


  std::unique_ptr<fb::Block> newBlock(BlockType blockType);
  std::unique_ptr<fb::Block> newRandom(BlockType excludedType = static_cast<BlockType>(-1));
public:
  class Clearing {
    friend class Block;

  private:
    std::set<std::shared_ptr<BlockBar>> bars;
    int64_t revealingTime;

  protected:
  public:
    void addBlockBar(std::shared_ptr<Panel::BlockBar> bar);
    bool isDoneRevealing(int64_t tick);
    void onDoneRevealing();
    bool contains(std::shared_ptr<fb::Block> block);
    bool isEmpty();
    void removeBar(std::shared_ptr<BlockBar> bar);
    void setRevealingTime(int64_t revealingTime);
  };

  uint32_t level;
  static const int32_t numberOfRegularBlocks = 5;
  bool scrollingEnabled;
  static const int32_t Y_DISPLAY = FuriousBlocksCoreDefaults::PANEL_HEIGHT;
  static const int32_t Y = Panel::Y_DISPLAY + (Panel::Y_DISPLAY * 4);
  std::array<std::array<std::shared_ptr<fb::Block>, Panel::Y>, Panel::X> blocks;
  furiousblocks::Point cursor;
  int32_t scrollingDelta;
  uint64_t score;
  bool gameOver;

  Panel(int32_t seed, int32_t playerId, std::array<std::array<BlockType, FuriousBlocksCoreDefaults::PANEL_HEIGHT>, FuriousBlocksCoreDefaults::PANEL_WIDTH> initialBlockTypes, PanelListener &panelListener);
  ~Panel();
  void reset();
  void setTransposedBlocks(std::vector<std::vector<BlockType>> & blockTypes);
  void onTick(int64_t tick);
  void stackGarbage(Panel::Garbage* garbage);
  Panel::Garbage* newGarbage(int32_t width, int32_t height, int32_t owner, bool skill);
  int64_t getLocalTick();
  void setLocalTick(int64_t localTick);
  bool isGameOver() const;
  void submitMove(std::unique_ptr<Move, MoveDeleter>&& move);
};

#endif //__Panel_H_
