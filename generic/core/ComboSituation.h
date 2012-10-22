#ifndef __ComboSituation_H_
#define __ComboSituation_H_

#include <cstdint>
#include <set>

class ComboSituation {
private:
  std::set<int32_t> blockIds;

protected:
public:
  ComboSituation(int32_t size, int32_t skillChainLevel, std::set<int32_t> blockIds);
  bool contains(int32_t blockId);
  int32_t size;
  int32_t skillChainLevel;
};

#endif //__ComboSituation_H_
