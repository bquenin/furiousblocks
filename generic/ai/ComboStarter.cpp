//
// Created by bquenin on 2/24/13.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "ComboStarter.h"

ComboStarter::ComboStarter(PanelHelper& helper)
: helper(helper)
, panel(helper.panel) {
}

std::unique_ptr<fb::Point> ComboStarter::compute() {
  // First, try to find an horizontal combo starter since it's generally preferable
  auto target = computeHorizontalStarter();

  // If no horizontal starter was found, try to find a vertical starter
  if (!target) {
    target = computeVerticalStarter();
  }

  return target;
}

std::unique_ptr<fb::Point> ComboStarter::computeHorizontalStarter() {
  auto target = std::unique_ptr<fb::Point>();
  for (int y = 1; y < panel.Y_DISPLAY - 1; y++) {
    int sameBlock[Panel::numberOfRegularBlocks] = {};
    for (int x = 0; x < panel.X; x++) {
      auto&& current = panel.blocks[x][y];
      if (!fb::Block::isComputable(current.get())) {
        continue;
      }
      sameBlock[static_cast<uint8_t>(current->type)]++;
    }
    for (uint8_t index = 0; index < Panel::numberOfRegularBlocks; index++) {
      if (sameBlock[index] >= 3) {
        target = getHorizontalComboPointOnLine(static_cast<BlockType>(index), y);
        if (target) {
          return target;
        }
      }
    }
  }
  return target;
}

std::unique_ptr<fb::Point> ComboStarter::getHorizontalComboPointOnLine(BlockType blockType, int line) {
  // Build a bit mask of blocks of Type blockType
  bool mask[panel.X];
  for (int x = 0; x < panel.X; x++) {
    mask[x] = false;
    auto&& current = panel.blocks[x][line];
    if (!fb::Block::isComputable(current.get())) {
      continue;
    }
    if (current->type != blockType) {
      continue;
    }
    mask[x] = true;
  }

  for (int i = 0; i < panel.X - 1; i++) {
    // 2 in a row
    if (mask[i] && mask[i + 1]) {
      // Check right
      for (int x = i + 2; x < panel.X - 1; x++) {
        if (mask[x + 1]) {
          if (helper.isBlockSwitchPossible(x, line)) {
            return std::unique_ptr<fb::Point>(new fb::Point(x, line));
          }
        }
      }
      // Check left
      for (int x = i - 2; x >= 0; x--) {
        if (mask[x]) {
          if (helper.isBlockSwitchPossible(x, line)) {
            return std::unique_ptr<fb::Point>(new fb::Point(x, line));
          }
        }
      }
    }

    // no consecutive blocks
    if (mask[i]) {
      // Check right
      for (int x = i + 1; x < panel.X - 1; x++) {
        if (mask[x + 1]) {
          if (helper.isBlockSwitchPossible(x, line)) {
            return std::unique_ptr<fb::Point>(new fb::Point(x, line));
          }
        }
      }
      // Check left
      for (int x = i - 2; x >= 0; x--) {
        if (mask[x]) {
          if (helper.isBlockSwitchPossible(x, line)) {
            return std::unique_ptr<fb::Point>(new fb::Point(x, line));
          }
        }
      }
    }
  }
  return std::unique_ptr<fb::Point>();
}

std::unique_ptr<fb::Point> ComboStarter::computeVerticalStarter() {
  /// We are looking for a vertical combo starter
  BlockType electedType;
  auto target = std::unique_ptr<fb::Point>();

  /// Start with the bottom row and go up
  for (int y = 1; y < panel.Y_DISPLAY - 1; y++) {
    for (int x = 0; x < panel.X; x++) {
      auto&& current = panel.blocks[x][y];
      if (!fb::Block::isComputable(current.get())) {
        continue;
      }
      // Just elect a type based on the current block
      electedType = current->type;

      // Check if the 2 above rows contains that type. If not, just continue
      if (!(helper.doesRowContainBlockType(y + 1, electedType) && helper.doesRowContainBlockType(y + 2, electedType))) {
        continue;
      }

      // Now that we know that the above rows contains the blocks we're looking for,
      // just assume they're right above our current block.
      // If both blocks were, a combo would have been triggered, so one of them is necessarily not aligned
      // We are now going to check the 2 rows above to check where the block is.

      // Enforce that the block is actually misaligned by checking the block 1 row above the current block is either null or
      // not of the right type
      // 1 row above
      auto closestBlockAbove = std::unique_ptr<fb::Point>();
      auto blockAboveAligned = true;
      if (!panel.blocks[x][y + 1] || panel.blocks[x][y + 1]->type != electedType) {
        // Then look for where the block is
        blockAboveAligned = false;
        closestBlockAbove = helper.getClosestBlockWithType(x, y + 1, electedType);
      }

      // Enforce that the block is actually misaligned by checking the block 2 rows above the current block is either null or
      // not of the right type
      // 2 rows above
      auto closestBlockAboveAbove = std::unique_ptr<fb::Point>();
      auto blockAboveAboveAligned = true;
      if (!panel.blocks[x][y + 2] || panel.blocks[x][y + 2]->type != electedType) {
        // Then look for where the block is
        blockAboveAboveAligned = false;
        closestBlockAboveAbove = helper.getClosestBlockWithType(x, y + 2, electedType);
      }

      // Both blocks misaligned
      if (!blockAboveAligned && !blockAboveAboveAligned) {
        // Make sure we can move the 2 blocks to the target
        if (!closestBlockAbove || !closestBlockAboveAbove) {
          continue;
        }
        if (closestBlockAbove) {
          return closestBlockAbove;
        } else {
          return closestBlockAboveAbove;
        }
      }

      if (blockAboveAboveAligned && closestBlockAbove) {
        return closestBlockAbove;
      }
      if (blockAboveAligned && closestBlockAboveAbove) {
        return closestBlockAboveAbove;
      }
    }
  }
  return target;
}
