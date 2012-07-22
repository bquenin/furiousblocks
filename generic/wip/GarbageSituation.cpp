#include "GarbageSituation.h"
using namespace std;

GarbageSituation::GarbageSituation(int width, int height, int owner, list<Integer*>* blocks)
:width(0), height(0), owner(0), blocks(nullptr)
{
    this->width = width;
    this->height = height;
    this->owner = owner;
    this->blocks = blocks;
}

int GarbageSituation::getWidth()
{
    return width;
}

int GarbageSituation::getHeight()
{
    return height;
}

int GarbageSituation::getOwner()
{
    return owner;
}

bool GarbageSituation::contains(int blockId)
{
    return blocks->contains(blockId);
}
