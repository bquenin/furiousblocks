#include <cstdint>
#include <set>
#include "ComboSituation.h"

ComboSituation::ComboSituation(int32_t size, int32_t skillChainLevel, std::set<int32_t> blockIds)
: size(size),skillChainLevel(skillChainLevel),blockIds(blockIds){
}

bool ComboSituation::contains(int32_t blockId) {
  return blockIds.find(blockId) != blockIds.end();
}
