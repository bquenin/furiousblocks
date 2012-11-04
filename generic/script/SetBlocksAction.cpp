#include "SetBlocksAction.h"

SetBlocksAction::SetBlocksAction(float timeStep, Panel &panel, const std::vector<const std::vector<BlockType>> &blockTypes)
: Action(timeStep)
, panel(panel)
, blockTypes(std::move(blockTypes)) {
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
