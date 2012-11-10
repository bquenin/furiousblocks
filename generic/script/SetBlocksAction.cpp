#include "SetBlocksAction.h"

SetBlocksAction::SetBlocksAction(float timeStep, Panel &panel, std::vector<std::vector<BlockType>> &blockTypes)
: Action(timeStep)
, panel(panel)
, blockTypes(blockTypes) {
}

bool SetBlocksAction::execute(float stateTime) {
  if (stateTime > nextStep) {
    panel.reset();
    panel.setTransposedBlocks(blockTypes);
    nextStep = stateTime + timeStep;
    return true;
  }
  return false;
}
