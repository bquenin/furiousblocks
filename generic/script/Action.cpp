#include "Action.h"

Action::Action(float timeStep)
: timeStep(timeStep)
, nextStep(0) {
}

void Action::setNextStep(float nextStep) {
  this->nextStep = nextStep;
}

float Action::getTimeStep() {
  return timeStep;
}
