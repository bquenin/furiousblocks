#ifndef __ComboSituation_H_
#define __ComboSituation_H_

#include <cstdint>
#include <set>

class ComboSituation
{
private:
    int32_t size = 0;
    int32_t skillChainLevel = 0;
    std::set<int32_t> blockIds;

protected:
public:
    ComboSituation(int32_t size, int32_t skillChainLevel, std::set<int32_t> blockIds);
    bool contains(int32_t blockId);
};

#endif //__ComboSituation_H_
