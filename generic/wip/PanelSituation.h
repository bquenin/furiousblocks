#ifndef __PanelSituation_H_
#define __PanelSituation_H_
#include "GarbageSituation.h"
#include "PanelState.h"
#include "PanelSituation.h"
#include "ComboSituation.h"
#include "Point.h"
using namespace std;
class PanelSituation
{
public:
    PanelSituation(BlockSituation*** blockSituations, bool isLocked, Collection<ComboSituation*>* comboSituations, Point* cursorPosition, int scrollingOffset, PanelState state, int stateTick, Collection<GarbageSituation*>* garbageSituations, Collection<GarbageSituation*>* garbageStackSituation, int skillChainLevel, int freezingTime, bool gameOver, int wallOffset, bool gracing, int score, bool clearing);
    BlockSituation* getBlockSituations();
    bool isLocked();
    Collection<ComboSituation*> getComboSituations();
    Point* getCursorPosition();
    int getScrollingOffset();
    PanelState getState();
    int getStateTick();
    int getSkillChainLevel();
    int getFreezingTime();
    bool isGameOver();
    int getWallOffset();
    bool isGracing();
    int getScore();
    GarbageSituation* getGarbageByBlock(int blockId);
    ComboSituation* getComboByBlock(int blockId);
    PanelSituation* getSimpleClone();
    bool isClearing();
    bool equals(Object* o);
    int hashCode();

protected:
private:
    BlockSituation*** blockSituations;
    bool isLocked;
    Collection<ComboSituation*>* comboSituations;
    Point* cursorPosition;
    int scrollingOffset;
    PanelState state;
    int stateTick;
    Collection<GarbageSituation*>* garbageSituations;
    Collection<GarbageSituation*>* garbageStackSituation;
    int skillChainLevel;
    int freezingTime;
    bool gameOver;
    int wallOffset;
    bool gracing;
    int score;
    bool clearing;
};
#endif //__PanelSituation_H_
