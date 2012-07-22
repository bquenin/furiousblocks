#ifndef __Combo_H_
#define __Combo_H_

#include "ComboSituation.h"
#include "Block.h"

using namespace std;

class Combo {
public:
  Combo(int owner);
  void addBlock(Block *block);
  set<Block *> getBlocks();
  int size();
  int getOwner();
  int getSkillChainLevel();
  ComboSituation *getSituation();
  bool contains(Block *block);

protected:
private:
  set<Block *> *blocks;
  int owner;
  int skillChainLevel;
};
#endif //__Combo_H_
