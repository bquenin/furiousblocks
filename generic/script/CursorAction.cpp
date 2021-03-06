#include "CursorAction.h"

CursorAction::CursorAction(float timeStep, TutorialPlayer &player, MoveType moveType)
: Action(timeStep)
, player(player)
, moveType(moveType) {
}

bool CursorAction::execute(float stateTime) {
  if (stateTime > nextStep) {
    player.setMove(moveType);
    nextStep = stateTime + timeStep;
    return true;
  }
  return false;
}
