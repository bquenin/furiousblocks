#ifndef __Panel_H_
#define __Panel_H_

#include <list>
#include <set>
#include "GarbageSituation.h"
#include "BlockSituation.h"
#include "PanelState.h"
#include "PanelSituation.h"
#include "SimpleRNG.h"
#include "Move.h"
#include "ComboSituation.h"
#include "PanelListener.h"
#include "Combo.h"
#include "Block.h"
#include "Point.h"
#include "Object.h"

using namespace std;
class Panel {
public:
  static const int numberOfRegularBlocks = 5;
  bool scrollingEnabled;
  Panel(int seed, int playerId, BlockType ***initialBlockTypes);
  Panel(int seed, int playerId, BlockType ***initialBlockTypes, PanelListener *panelListener);
  void reset();
  void setTransposedBlocks(BlockType ***initialBlockTypes);
  PanelSituation *onTick(long tick);
  void stackGarbage(Garbage *garbage);
  Garbage *newGarbage(int width, int height, int owner, bool skill);
  long getLocalTick();
  void setLocalTick(long localTick);
  bool isGameOver();
  void submitMove(Move *move);
  int hashCode();
  bool equals(Object *obj);

protected:
  static const int X = FuriousBlocksCoreDefaults::PANEL_WIDTH;
  static const int Y = Panel::Y_DISPLAY + (Panel::Y_DISPLAY * 4);
  Block *blocks[Panel::X][Panel::Y];
  Block *newRandom(BlockType excludedType);
  Block *newBlock(BlockType blockType);

private:
  class BlockBar {
  public:
    bool contains(Block *block);
    bool hasToFall(int xOrigin, int yOrigin);
    void fall(int xOrigin, int yOrigin);
    void idle();
    int blink(int poppingIndex);
    bool isRevealing();
    int hashCode();
    bool equals(Object *obj);

  protected:
  private:
    int id;
    int width;
    int height;
    int owner;
    set<Block *> *barBlocks;
    Panel *__parent;
    BlockBar(Panel *__parent, int width, int height, int owner);
    virtual void onDoneRevealing() = 0;
  };
  class Garbage {
  public:
    bool isSkill();
    int getOwner();
    int blink(int poppingIndex, Combo *combo);
    int reveal(int xOrigin, int yOrigin, int revealingTime, Clearing *parentClearing);
    GarbageSituation *getSituation();

  protected:
  private:
    bool skill;
    Combo *triggeringCombo;
    Panel *__parent;
    Garbage(Panel *__parent, int width, int height, int owner, bool skill);
    void inject(int x, int y);
    void onDoneRevealing();
  };
  class BlockLine {
  public:
    int reveal(int xOrigin, int yOrigin, int revealingTime);

  protected:
  private:
    Panel *__parent;
    BlockLine(Panel *__parent, int width, int owner);
    void inject(int x, int y);
    void onDoneRevealing();
  };

  class Clearing {
  public:
    void addBlockBar(BlockBar *bar);
    bool isDoneRevealing(long tick);
    void onDoneRevealing();
    bool contains(Block *block);
    bool isEmpty();
    void removeBar(BlockBar *bar);
    void setRevealingTime(long revealingTime);

  protected:
  private:
    set<BlockBar *> bars;
    long revealingTime;
  };

  static const int Y_DISPLAY = FuriousBlocksCoreDefaults::PANEL_HEIGHT;
  static const int INITIAL_SCROLLING_SPEED = TODOCastExpression;
  static const long NEXT_LEVEL = TODOCastExpression;
  int lastIndex;
  SimpleRNG *random;
  long localTick;
  int playerId;
  Point *cursor;
  list<Combo *> combos;
  list<Garbage *> garbages;
  set<Clearing *> clearings;
  list<Garbage *> garbageStack;
  PanelState state;
  int stateTick;
  int levelScrollingSpeed;
  int scrollingSpeed;
  int scrollingDelta;
  int freezingTime;
  int bonusFreezingTime;
  int skillChainLevel;
  Move *move;
  bool locked;
  bool lifting;
  bool gracing;
  bool gameOver;
  int wallOffset;
  int score;
  PanelListener *panelListener;
  Block *newRandom(BlockType excludedType, int poppingIndex, int skillChainLevel);
  Block *newBlock(BlockType blockType, int index, int skillChainLevel);
  void processMove();
  void dropGarbages();
  void scrolling(long tick);
  void gracePeriod();
  void freeze(int freezingTime);
  void newLine();
  void quake();
  void mechanics(long tick);
  Combo *getComboByBlock(Block *block);
  Garbage *getGarbageByBlock(Block *block);
  Combo *detectCombo();
  void processCombo(Combo *combo);
  PanelSituation *getSituation();
};
#endif //__Panel_H_
