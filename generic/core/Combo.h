#ifndef __Combo_H_
#define __Combo_H_

#include <cstdint>
#include <vector>
#include "Block.h"
#include "ComboSituation.h"

class Combo {
private:
protected:
public:
  std::vector<Block *> blocks;
  int32_t owner;
  int32_t skillChainLevel;
  Combo(int32_t owner);
  void addBlock(Block *block);
  int32_t size();
  ComboSituation *getSituation();
  bool contains(Block *block);
};

#endif //__Combo_H_
