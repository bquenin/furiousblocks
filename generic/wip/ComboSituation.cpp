#include "ComboSituation.h"
using namespace std;

ComboSituation::ComboSituation(int size, int skillChainLevel, list<Integer*>* blockIds)
:size(0), skillChainLevel(0), blockIds(nullptr)
{
    this->size = size;
    this->skillChainLevel = skillChainLevel;
    this->blockIds = blockIds;
}

int ComboSituation::getSkillChainLevel()
{
    return skillChainLevel;
}

int ComboSituation::getSize()
{
    return size;
}

bool ComboSituation::contains(int blockId)
{
    return blockIds->contains(blockId);
}
