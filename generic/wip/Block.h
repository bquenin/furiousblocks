#ifndef __Block_H_
#define __Block_H_

#include "BlockSituation.h"
#include "Clearing.h"
#include "BlockType.h"
#include "FuriousBlocksCoreDefaults.h"
#include "PanelEvent.h"
#include "BlockState.h"

class Block {
public:
  int getId();
  BlockType getType();
  BlockState getState();
  int getStateTick();
  void setGarbageOwner(int garbageOwner);
  bool isFallingFromClearing();
  void setFallingFromClearing(bool fallingFromClearing);
  void setCombo();
  int getGarbageBlockType();
  void setGarbageBlockType(int garbageBlockType);
  int getPoppingIndex();
  void setPoppingIndex(int poppingIndex);
  int getPoppingSkillChainLevel();
  void setPoppingSkillChainLevel(int poppingSkillChainLevel);
  void setJustLand();
  bool hasJustLand();
  void idle();
  void switchBack();
  void switchForth();
  void hover();
  void fall();
  void land();
  void blink();
  void explode(int explodingTime);
  void reveal(int revealingTime);
  void airBounce();
  void delete();
  PanelEvent *update();
  BlockSituation *getSituation();
  static bool isComputable(Block *block);
  void setClearing(Clearing *clearing);
  Clearing *getClearing();

protected:
private:
  int id;
  BlockType type;
  BlockState state;
  int stateTick;
  int garbageBlockType;
  int garbageOwner;
  int poppingIndex;
  int poppingSkillChainLevel;
  bool combo;
  bool fallingFromClearing;
  bool justLand;
  bool movable;
  bool combinable;
  Clearing *clearing;
  Block(int id, BlockType type, int index, int skillChainLevel);
};
#endif //__Block_H_
