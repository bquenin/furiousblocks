#ifndef __Combo_H_
#define __Combo_H_

#include <cstdint>
#include <vector>
#include "Block.h"

class Combo {
private:
protected:
public:
  std::vector<Block *> blocks;
  int32_t owner;
  int32_t skillChainLevel;
  int32_t x;
  int32_t y;
  Combo(int32_t owner);
  void addBlock(Block *block);
  int32_t size();
  bool contains(Block *block);
};

#endif //__Combo_H_
