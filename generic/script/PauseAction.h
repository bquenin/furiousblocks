#include "Action.h"

#ifndef __PauseAction_H_
#define __PauseAction_H_


class PauseAction : Action {
private:
protected:
public:
  PauseAction(float timeStep);
  bool execute(float stateTime);
};

#endif //__PauseAction_H_
