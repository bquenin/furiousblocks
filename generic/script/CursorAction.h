#ifndef __CursorAction_H_
#define __CursorAction_H_

#include <cstdint>
#include "Action.h"
#include "TutorialPlayer.h"

class CursorAction : Action {
private:
  TutorialPlayer *player = nullptr;
  int8_t moveType = 0;

protected:
public:
  CursorAction(float timeStep, TutorialPlayer *player, int8_t moveType);
  bool execute(float stateTime);
};

#endif //__CursorAction_H_
