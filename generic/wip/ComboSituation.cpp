#include <cstdint>
#include <list>
#include <unordered_set>
#include "ComboSituation.h"

using namespace std;

ComboSituation::ComboSituation(int32_t size, int32_t skillChainLevel, unordered_set<int32_t> &blockIds) :
size(size), skillChainLevel(skillChainLevel), blockIds(blockIds) {
}

bool ComboSituation::contains(int32_t blockId) {
  return blockIds.find(blockId) != blockIds.end();
}
