#ifndef __GarbageSituation_H_
#define __GarbageSituation_H_
using namespace std;
class GarbageSituation
{
public:
    GarbageSituation(int width, int height, int owner, list<Integer*>* blocks);
    int getWidth();
    int getHeight();
    int getOwner();
    bool contains(int blockId);

protected:
private:
    int width;
    int height;
    int owner;
    list<Integer*>* blocks;
};
#endif //__GarbageSituation_H_
