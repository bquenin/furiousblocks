#include <cstdint>
#include <set>
#include "Combo.h"

Combo::Combo(int32_t owner)
:owner(owner), skillChainLevel(1) {
}

void Combo::addBlock(Block *block) {
  blocks.insert(block);
}

int32_t Combo::size() {
  return blocks.size();
}

ComboSituation *Combo::getSituation() {
  std::set<int32_t> blockIds;
  for (auto block: blocks) {
    blockIds.insert(block->id);
  }
  return new ComboSituation(blocks.size(), skillChainLevel, blockIds);
}

bool Combo::contains(Block *block) {
  return blocks.find(block) != blocks.end();
}
