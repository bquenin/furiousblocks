#include "Action.h"

void Action::setNextStep(float nextStep) {
  this->nextStep = nextStep;
}

float Action::getTimeStep() {
  return timeStep;
}
