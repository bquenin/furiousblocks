#include "SetBlocksAction.h"

SetBlocksAction::SetBlocksAction(float timeStep, Panel *panel, BlockType **blockTypes, size_t xLen, size_t yLen)
: Action(timeStep)
, panel(panel)
, blockTypes(blockTypes)
, xLen(xLen)
, yLen(yLen)
{
}

bool SetBlocksAction::execute(float stateTime) {
  if (stateTime > nextStep) {
    panel->reset();
    panel->setTransposedBlocks(blockTypes, xLen, yLen);
    nextStep = stateTime + timeStep;
    return true;
  }
  return false;
}
