#ifndef __ComboSituation_H_
#define __ComboSituation_H_
using namespace std;
class ComboSituation
{
public:
    ComboSituation(int size, int skillChainLevel, list<Integer*>* blockIds);
    int getSkillChainLevel();
    int getSize();
    bool contains(int blockId);

protected:
private:
    int size;
    int skillChainLevel;
    list<Integer*>* blockIds;
};
#endif //__ComboSituation_H_
