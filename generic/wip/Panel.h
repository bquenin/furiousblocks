#ifndef __Panel_H_
#define __Panel_H_

#include <cstdint>
#include <set>
#include <list>
#include <MacTypes.h>
#include "Block.h"
#include "Combo.h"
#include "GarbageSituation.h"
#include "FuriousBlocksCoreDefaults.h"
#include "SimpleRNG.h"
#include "BlockType.h"
#include "PanelListener.h"
#include "Move.h"
#include "PanelState.h"
#include "PanelSituation.h"
#include "Point.h"

class Panel {
  friend class Clearing;
private:
  class BlockBar {
    friend class Clearing;
  private:
    int32_t id = 0;
    int32_t owner = 0;
    Panel *__parent;
    BlockBar(Panel *__parent, int32_t width, int32_t height, int32_t owner);
    virtual void onDoneRevealing() = 0;

  protected:
  public:
    bool contains(Block *block);
    bool hasToFall(int32_t xOrigin, int32_t yOrigin);
    void fall(int32_t xOrigin, int32_t yOrigin);
    void idle();
    int32_t blink(int32_t poppingIndex);
    bool isRevealing();
    int32_t width = 0;
    int32_t height = 0;
    std::set<Block *> barBlocks;
  };
  class Garbage : BlockBar {
  private:
    bool skill = false;
    Combo *triggeringCombo = nullptr;
    Panel *__parent;
    Garbage(Panel *__parent, int32_t width, int32_t height, int32_t owner, bool skill);
    void inject(int32_t x, int32_t y);
    void onDoneRevealing();

  protected:
  public:
    bool isSkill();
    int32_t getOwner();
    int32_t blink(int32_t poppingIndex, Combo *combo);
    int32_t reveal(int32_t xOrigin, int32_t yOrigin, int32_t revealingTime, Clearing *parentClearing);
    GarbageSituation *getSituation();
  };
  class BlockLine : BlockBar {
  private:
    Panel *__parent;
    BlockLine(Panel *__parent, int32_t width, int32_t owner);
    void inject(int32_t x, int32_t y);
    void onDoneRevealing();

  protected:
  public:
    int32_t reveal(int32_t xOrigin, int32_t yOrigin, int32_t revealingTime);
  };
  static const int32_t INITIAL_SCROLLING_SPEED = static_cast<int32_t>(FuriousBlocksCoreDefaults::CORE_FREQUENCY);
  static const int64_t NEXT_LEVEL = static_cast<int64_t>((FuriousBlocksCoreDefaults::CORE_FREQUENCY * 1000));
  int32_t lastIndex = -1;
  SimpleRNG *random = nullptr;
  int64_t localTick = 0;
  int32_t playerId = 0;
  furiousblocks::Point *cursor;
  std::list<Combo *> combos;
  std::list<Panel::Garbage *> garbages;
  std::set<Clearing *> clearings;
  std::list<Panel::Garbage *> garbageStack;
  PanelState state = PanelState::IDLE;
  int32_t stateTick = 0;
  int32_t levelScrollingSpeed = 0;
  int32_t scrollingSpeed = 0;
  int32_t scrollingDelta = 0;
  int32_t freezingTime = 0;
  int32_t bonusFreezingTime = 0;
  int32_t skillChainLevel = 1;
  Move *move = nullptr;
  bool locked = false;
  bool lifting = false;
  bool gracing = false;
  bool gameOver = false;
  int32_t wallOffset = 0;
  int32_t score = 0;
  PanelListener *panelListener = nullptr;
  Block *newRandom(BlockType excludedType, int32_t poppingIndex, int32_t skillChainLevel);
  Block *newBlock(BlockType blockType, int32_t index, int32_t skillChainLevel);
  void processMove();
  void dropGarbages();
  void scrolling(int64_t tick);
  void gracePeriod();
  void freeze(int32_t freezingTime);
  void newLine();
  void quake();
  void mechanics(int64_t tick);
  Combo *getComboByBlock(Block *block);
  Panel::Garbage *getGarbageByBlock(Block *block);
  Combo *detectCombo();
  void processCombo(Combo *combo);
  PanelSituation *getSituation();

protected:
  static const int32_t X = FuriousBlocksCoreDefaults::PANEL_WIDTH;

  Block *newRandom(BlockType excludedType);
  Block *newBlock(BlockType blockType);

public:
  static const int32_t numberOfRegularBlocks = 5;
  bool scrollingEnabled = true;
  Panel(int32_t seed, int32_t playerId, BlockType ***initialBlockTypes);
  Panel(int32_t seed, int32_t playerId, BlockType ***initialBlockTypes, PanelListener *panelListener);
  void reset();
  void setTransposedBlocks(BlockType ***initialBlockTypes);
  PanelSituation *onTick(int64_t tick);
  void stackGarbage(Panel::Garbage *garbage);
  Panel::Garbage *newGarbage(int32_t width, int32_t height, int32_t owner, bool skill);
  int64_t getLocalTick();
  void setLocalTick(int64_t localTick);
  bool isGameOver();
  void submitMove(Move *move);
  static const int32_t Y_DISPLAY = FuriousBlocksCoreDefaults::PANEL_HEIGHT;
  static const int32_t Y = Panel::Y_DISPLAY + (Panel::Y_DISPLAY * 4);
  Block *blocks[Panel::X][Panel::Y];
};

#endif //__Panel_H_
