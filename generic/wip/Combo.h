#ifndef __Combo_H_
#define __Combo_H_

#include <cstdint>
#include <unordered_set>
#include <list>
#include "ComboSituation.h"
#include "Block.h"

using namespace std;

class Combo {
public:
  unordered_set<Block *> blocks;
  int32_t owner = 0;
  int32_t skillChainLevel = 1;
  
  Combo(int32_t owner);
  void addBlock(Block& block);
  int32_t size();
  ComboSituation getSituation();
  bool contains(Block& block);
};

#endif //__Combo_H_
