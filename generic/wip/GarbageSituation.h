#ifndef __GarbageSituation_H_
#define __GarbageSituation_H_

#include <cstdint>
#include <set>

class GarbageSituation
{
private:
    int32_t width = 0;
    int32_t height = 0;
    int32_t owner = 0;
    std::set<int32_t> blocks;

protected:
public:
    GarbageSituation(int32_t width, int32_t height, int32_t owner, std::set<int32_t> blocks);
    bool contains(int32_t blockId);
};

#endif //__GarbageSituation_H_
