#include <cstdint>
#include <unordered_set>
#include <list>
#include "ComboSituation.h"
#include "Combo.h"

using namespace std;

Combo::Combo(int32_t owner) {
  this->owner = owner;
}

void Combo::addBlock(Block& block) {
  blocks.insert(&block);
}

int32_t Combo::size() {
  return blocks.size();
}

ComboSituation Combo::getSituation() {
  unordered_set<int32_t> blockIds;
  for (const auto block: blocks) {
    blockIds.insert(block->id);
  }
  return ComboSituation(blocks.size(), skillChainLevel, blockIds);
}

bool Combo::contains(Block& block) {
  return blocks.find(&block) != blocks.end();
}
