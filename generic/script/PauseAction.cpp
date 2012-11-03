#include "PauseAction.h"

PauseAction::PauseAction(float timeStep) {
  this->timeStep = timeStep;
}

bool PauseAction::execute(float stateTime) {
  return stateTime > nextStep;
}
