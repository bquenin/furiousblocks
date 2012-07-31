#include <cstdint>
#include <set>
#include "GarbageSituation.h"

GarbageSituation::GarbageSituation(int32_t width, int32_t height, int32_t owner, std::set<int32_t> blocks) {
  this->width = width;
  this->height = height;
  this->owner = owner;
  this->blocks = blocks;
}

bool GarbageSituation::contains(int32_t blockId) {
  return blocks.find(blockId) != blocks.end();
}
