#ifndef __CursorAction_H_
#define __CursorAction_H_

#include <cstdint>
#include "Action.h"
#include "TutorialPlayer.h"
#include "MoveType.h"

class CursorAction : public Action {
private:
  TutorialPlayer *player;
  MoveType moveType;

protected:
public:
  CursorAction(float timeStep, TutorialPlayer *player, MoveType moveType);
  bool execute(float stateTime);
};

#endif //__CursorAction_H_
