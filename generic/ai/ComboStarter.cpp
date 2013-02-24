//
// Created by bquenin on 2/24/13.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "ComboStarter.h"

ComboStarter::ComboStarter(PanelHelper& helper)
: helper(helper) {
}

std::unique_ptr<fb::Point> ComboStarter::compute() {
  // First, try to find an horizontal combo starter since it's generally preferable
  auto target = computeHorizontalStarter();

  // If no horizontal starter was found, try to find a vertical starter
  if (!target) {
    target = computeVerticalStarter();
  }

  return std::move(target);
}

std::unique_ptr<fb::Point> ComboStarter::computeHorizontalStarter() {
  auto target = std::unique_ptr<fb::Point>();
  for (int y = 1; y < helper.panel.Y_DISPLAY - 1; y++) {
    int sameBlock[Panel::numberOfRegularBlocks] = {};
    for (int x = 0; x < helper.panel.X; x++) {
      auto&& current = helper.panel.blocks[x][y];
      if (!fb::Block::isComputable(current.get())) {
        continue;
      }
      sameBlock[static_cast<uint8_t>(current->type)]++;
    }
    for (uint8_t index = 0; index < Panel::numberOfRegularBlocks; index++) {
      if (sameBlock[index] >= 3) {
        target = getHorizontalComboPointOnLine(static_cast<BlockType>(index), y);
        if (target) {
          return std::move(target);
        }
      }
    }
  }
  return std::move(target);
}

std::unique_ptr<fb::Point> ComboStarter::getHorizontalComboPointOnLine(BlockType blockType, int line) {
  // Build a bit mask of blocks of Type blockType
  bool mask[helper.panel.X];
  for (int x = 0; x < helper.panel.X; x++) {
    mask[x] = false;
    auto&& current = helper.panel.blocks[x][line];
    if (!fb::Block::isComputable(current.get())) {
      continue;
    }
    if (current->type != blockType) {
      continue;
    }
    mask[x] = true;
  }

  // 2 in a row
  for (int i = 0; i < (helper.panel.X - 1); i++) {
    if (mask[i] && mask[i + 1]) {
      // Check right
      for (int x = i + 2; x < (helper.panel.X - 1); x++) {
        if (mask[x + 1]) {
          if (helper.isBlockSwitchPossible(x, line)) {
            return std::move(std::unique_ptr<fb::Point>(new fb::Point(x, line)));
          }
        }
      }
      // check left
      for (int x = i - 2; x >= 0; x--) {
        if (mask[x]) {
          if (helper.isBlockSwitchPossible(x, line)) {
            return std::move(std::unique_ptr<fb::Point>(new fb::Point(x, line)));
          }
        }
      }
    }
  }

  // no consecutive blocks
  for (int i = 0; i < (helper.panel.X - 1); i++) {
    if (mask[i]) {
      // check right
      for (int x = i + 1; x < (helper.panel.X - 1); x++) {
        if (mask[x + 1]) {
          if (helper.isBlockSwitchPossible(x, line)) {
            return std::move(std::unique_ptr<fb::Point>(new fb::Point(x, line)));
          }
        }
      }
      // check left
      for (int x = i - 2; x >= 0; x--) {
        if (mask[x]) {
          if (helper.isBlockSwitchPossible(x, line)) {
            return std::move(std::unique_ptr<fb::Point>(new fb::Point(x, line)));
          }
        }
      }
    }
  }
  return std::move(std::unique_ptr<fb::Point>());
}

std::unique_ptr<fb::Point> ComboStarter::computeVerticalStarter() {
  /// We are looking for a vertical combo starter
  BlockType electedType;
  auto target = std::unique_ptr<fb::Point>();

  /// Start with the bottom row and go up
  for (int y = 1; y < helper.panel.Y_DISPLAY - 1; y++) {
    for (int x = 0; x < helper.panel.X; x++) {
      auto&& current = helper.panel.blocks[x][y];
      if (!fb::Block::isComputable(current.get())) {
        continue;
      }
      // Just elect a type based on the current block
      electedType = current->type;

      // Check if the 2 above rows contains that type. If not, just continue
      if (!(doesRowContainBlockType(y + 1, electedType) && doesRowContainBlockType(y + 2, electedType))) {
        continue;
      }

      // Now that we know that the above rows contains the blocks we're looking for,
      // just assume they're right above our current block.
      // If both blocks were, a combo would have been triggered, so one of them is necessarily not aligned
      // We are now going to check the 2 rows above to check where the block is.

      // Enforce that the block is actually misaligned by checking the block 1 row above the current block is either null or
      // not of the right type
      // 1 row above
      if (!helper.panel.blocks[x][y + 1] || helper.panel.blocks[x][y + 1]->type != electedType) {
        // Then look for where the block is
        auto closestBlock = getClosestTypedBlock(x, y + 1, electedType);
        if (!closestBlock) {
          continue;
        }
        return std::move(closestBlock);
      }

      // Enforce that the block is actually misaligned by checking the block 2 rows above the current block is either null or
      // not of the right type
      // 2 rows above
      if (!helper.panel.blocks[x][y + 2] || helper.panel.blocks[x][y + 2]->type != electedType) {
        // Then look for where the block is
        auto closestBlock = getClosestTypedBlock(x, y + 2, electedType);
        if (!closestBlock) {
          continue;
        }
        return std::move(closestBlock);
      }
    }
  }
  return std::move(target);
}

bool ComboStarter::doesRowContainBlockType(int row, BlockType blockType) {
  for (int x = 0; x < helper.panel.X; x++) {
    auto&& current = helper.panel.blocks[x][row];
    if (!fb::Block::isComputable(current.get())) {
      continue;
    }
    if (current->type != blockType) {
      continue;
    }
    return true;
  }
  return false;
}

std::unique_ptr<fb::Point> ComboStarter::getClosestTypedBlock(int column, int row, BlockType type) {
  // First check on the left
  auto closestBlockLeft = std::unique_ptr<fb::Point>();

  for (int x = column - 1; x >= 0; x--) {
    auto&& current = helper.panel.blocks[x][row];
    // If the block is null or its type is not the one we expect, just continue
    if (!current || current->type != type) {
      continue;
    }
    // If the blocks are not switchable for any reason, just break
    if (!helper.isBlockSwitchPossible(x, row)) {
      break;
    }
    closestBlockLeft.reset(new fb::Point(x, row));
    break;
  }

  // Then check on the right
  auto closestBlockRight = std::unique_ptr<fb::Point>();

  for (int x = column; x < helper.panel.X - 1; x++) {
    auto&& current = helper.panel.blocks[x + 1][row];
    // If the block is null or its type is not the one we expect, just continue
    if (!current || current->type != type) {
      continue;
    }
    // If the blocks are not switchable for any reason, just break
    if (!helper.isBlockSwitchPossible(x, row)) {
      break;
    }
    closestBlockRight.reset(new fb::Point(x, row));
    break;
  }

  if (closestBlockLeft && !closestBlockRight) {
    return std::move(closestBlockLeft);
  }
  if (!closestBlockLeft && closestBlockRight) {
    return std::move(closestBlockRight);
  }
  if (!closestBlockLeft && !closestBlockRight) {
    return std::move(std::unique_ptr<fb::Point>());
  }

  int deltax = column - closestBlockLeft->x;
  int deltay = closestBlockRight->x - column;

  if (deltax > deltay) {
    return std::move(closestBlockRight);
  }
  if (deltay > deltax) {
    return std::move(closestBlockLeft);
  }
  return std::move(closestBlockLeft);
}
