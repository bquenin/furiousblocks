#ifndef __GarbageSituation_H_
#define __GarbageSituation_H_

#include <cstdint>
#include <unordered_set>

class GarbageSituation {
private:
  int32_t width;
  int32_t height;
  int32_t owner;
  std::unordered_set<int32_t> blocks;

protected:
public:
  GarbageSituation(int32_t width, int32_t height, int32_t owner, std::unordered_set<int32_t> blocks);
  bool contains(int32_t blockId);
};

#endif //__GarbageSituation_H_
