#include <algorithm>
#include <set>
#include <iostream>
#include "Combo.h"

Combo::Combo(int32_t owner)
: owner(owner)
, skillChainLevel(1) {
}

void Combo::addBlock(std::shared_ptr<fb::Block> block) {
  blocks.push_back(block);
}

int32_t Combo::size() {
  return blocks.size();
}

bool Combo::contains(fb::Block* block) {
  return std::find_if(blocks.begin(), blocks.end(), [&block] (std::shared_ptr<fb::Block> const& i){return i.get() == block;}) != blocks.end();
}
