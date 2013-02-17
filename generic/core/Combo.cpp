#include <cstdint>
#include <set>
#include <iostream>
#include <algorithm>
#include "Combo.h"

Combo::Combo(int32_t owner)
: owner(owner)
, skillChainLevel(1) {
}

void Combo::addBlock(std::shared_ptr<fb::Block> block) {
  blocks.insert(block);
}

int32_t Combo::size() {
  return blocks.size();
}

bool Combo::contains(fb::Block* block) {
  auto found = std::find_if(blocks.begin(), blocks.end(), [block](std::shared_ptr<fb::Block> const& i){
    return i.get() == block;
  });
  return found != blocks.end();
//  for (auto i = blocks.begin(); i != blocks.end(); ++i) {
//    if ((*i).get() == block) {
//      return true;
//    }
//  }
//  return false;
}
