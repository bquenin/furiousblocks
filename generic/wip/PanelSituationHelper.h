#ifndef __PanelSituationHelper_H_
#define __PanelSituationHelper_H_
#include "BlockSituation.h"
#include "PanelSituation.h"
#include "BlockType.h"
#include "Point.h"
#include "BlockState.h"
using namespace std;
class PanelSituationHelper
{
public:
    PanelSituationHelper(PanelSituation* panelSituation);
    PanelSituation* getPanelSituation();
    int getHeight();
    bool isBlockSwitchPossible(Point* location);
    bool isAnyBlockSwitching();
    bool isAnyBlockFallingOrHoveringOrAirBouncing();
    bool isClearingGarbage();
    bool blockSwitchAndDetectFalling(int x, int y);
    bool detectCombo();
    int isGarbaged();
    bool isLineEmpty(int line);

protected:
private:
    PanelSituation* panelSituation;
    BlockSituation* blockSituations;
};
#endif //__PanelSituationHelper_H_
