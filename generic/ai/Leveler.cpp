//
// Created by bquenin on 2/26/13.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "Leveler.h"

Leveler::Leveler(PanelHelper& helper)
: helper(helper)
, panel(helper.panel) {
}

std::unique_ptr<fb::Point> Leveler::compute() {
  // Find the lowest empty block
  auto&& lowestEmptyBlock = findLowestEmptyBlock();

  // If we found one, we need to get the closest block on the line above this block.
  // If this block exists, it is where we need to move
  if (lowestEmptyBlock) {
    return helper.getClosestBlock(lowestEmptyBlock->x, lowestEmptyBlock->y + 1);
  }
  return std::unique_ptr<fb::Point>();
}

// TODO: Need to update this when the garbages are available
std::unique_ptr<fb::Point> Leveler::findLowestEmptyBlock() {
  for (int y = 1; y < panel.Y_DISPLAY; y++) {
    // Assume the line is empty
    bool emptyLine = true;

    // Actually check the line
    for (int x = 0; x < panel.X; x++) {
      // If the block is empty and the above block is "movable", then pick this block to level.
      // We're checking the block above to make sure that we can actually move a block to this position
      // on the line above
      // TODO: Maybe we should use isBlockSwitchPossible in order to make sure there is actually a possible move
      if (!panel.blocks[x][y]) {
        if (fb::Block::isMovable(panel.blocks[x][y + 1].get())) {
          return std::unique_ptr<fb::Point>(new fb::Point(x, y));
        }
      } else {
        emptyLine = false;
      }
    }

    // The line is empty, we should have returned a block before ...
    // If we didn't, then leveling is done
    if (emptyLine) {
      return std::unique_ptr<fb::Point>();
    }
  }
  return std::unique_ptr<fb::Point>();
}
