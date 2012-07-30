#include <cstdint>
#include <list>
#include "GarbageSituation.h"

using namespace std;

GarbageSituation::GarbageSituation(int32_t width, int32_t height, int32_t owner, unordered_set<int32_t> blocks) :
width(width), height(height), owner(owner), blocks(blocks) {
}

bool GarbageSituation::contains(int32_t blockId) {
  return blocks.find(blockId) != blocks.end();
}
