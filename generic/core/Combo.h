#ifndef __Combo_H_
#define __Combo_H_

#include <cstdint>
#include <vector>
#include "Block.h"

class Combo {
private:
protected:
public:
  std::vector<std::shared_ptr<fb::Block>> blocks;
  /// Vector because the renderer needs to clear the blocks in a defined order.
  int32_t owner;
  int32_t skillChainLevel;
  int32_t x;
  int32_t y;
  Combo(int32_t owner);
  void addBlock(std::shared_ptr<fb::Block> block);
  int32_t size();
  bool contains(fb::Block* block);
};

#endif //__Combo_H_
