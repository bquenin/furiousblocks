#include "SetBlocksAction.h"

SetBlocksAction::SetBlocksAction(float timeStep, Panel *panel, BlockType ***blockTypes) {
  this->panel = panel;
  this->blockTypes = blockTypes;
  this->timeStep = timeStep;
}

bool SetBlocksAction::execute(float stateTime) {
  if (stateTime > nextStep) {
    panel->reset();
    panel->setTransposedBlocks(lockTypes);
    nextStep = stateTime + timeStep;
    return true;
  }
  return false;
}
