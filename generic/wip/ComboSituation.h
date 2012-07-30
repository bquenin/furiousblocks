#ifndef __ComboSituation_H_
#define __ComboSituation_H_

#include <cstdint>
#include <unordered_set>

using namespace std;

class ComboSituation {
private:
  int32_t size = 0;
  int32_t skillChainLevel = 0;
  unordered_set<int32_t> blockIds;

protected:
public:
  ComboSituation(int32_t size, int32_t skillChainLevel, unordered_set<int32_t> &blockIds);
  bool contains(int32_t blockId);
};

#endif //__ComboSituation_H_
