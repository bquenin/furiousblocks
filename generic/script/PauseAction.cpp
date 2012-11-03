#include "PauseAction.h"

PauseAction::PauseAction(float timeStep)
: Action(timeStep) {
}

bool PauseAction::execute(float stateTime) {
  return stateTime > nextStep;
}
