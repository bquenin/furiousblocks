#include <cstdint>
#include "CursorAction.h"

CursorAction::CursorAction(float timeStep, TutorialPlayer *player, int8_t moveType) {
  this->player = player;
  this->moveType = moveType;
  this->timeStep = timeStep;
}

bool CursorAction::execute(float stateTime) {
  if (stateTime > nextStep) {
    player->setMove(moveType);
    nextStep = stateTime + timeStep;
    return true;
  }
  return false;
}
