#include "Action.h"

Action::Action(float timeStep)
: timeStep(timeStep) {
}

void Action::setNextStep(float nextStep) {
  this->nextStep = nextStep;
}

float Action::getTimeStep() {
  return timeStep;
}
