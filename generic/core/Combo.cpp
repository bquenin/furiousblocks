#include <cstdint>
#include <set>
#include "Combo.h"

Combo::Combo(int32_t owner)
: owner(owner)
, skillChainLevel(1) {
}

void Combo::addBlock(Block *block) {
  blocks.push_back(block);
}

int32_t Combo::size() {
  return blocks.size();
}

bool Combo::contains(Block *block) {
  for (Block *b : blocks) {
    if (b == block) {
      return true;
    }
  }
  return false;
}
