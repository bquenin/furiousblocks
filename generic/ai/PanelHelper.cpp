//
// Created by bquenin on 2/24/13.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "PanelHelper.h"

bool PanelHelper::isBlockSwitchPossible(int x, int y) const {
  return fb::Block::isMovable(panel.blocks[x][y].get()) && fb::Block::isMovable(panel.blocks[x + 1][y].get());
}

bool PanelHelper::doesRowContainBlockType(int row, BlockType blockType) {
  for (int x = 0; x < panel.X; x++) {
    auto&& current = panel.blocks[x][row];
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

std::unique_ptr<fb::Point> PanelHelper::getClosestBlockWithType(int column, int row, BlockType type) {
  // First check on the left
  auto closestBlockLeft = std::unique_ptr<fb::Point>();

  for (int x = column - 1; x >= 0; x--) {
    auto&& current = panel.blocks[x][row];
    // If the block is null or its type is not the one we expect, just continue
    if (!current || current->type != type) {
      continue;
    }
    // If the blocks are not switchable for any reason, just break
    if (!isBlockSwitchPossible(x, row)) {
      break;
    }
    closestBlockLeft.reset(new fb::Point(x, row));
    break;
  }

  // Then check on the right
  auto closestBlockRight = std::unique_ptr<fb::Point>();

  for (int x = column; x < panel.X - 1; x++) {
    auto&& current = panel.blocks[x + 1][row];
    // If the block is null or its type is not the one we expect, just continue
    if (!current || current->type != type) {
      continue;
    }
    // If the blocks are not switchable for any reason, just break
    if (!isBlockSwitchPossible(x, row)) {
      break;
    }
    closestBlockRight.reset(new fb::Point(x, row));
    break;
  }

  if (closestBlockLeft && !closestBlockRight) {
    return closestBlockLeft;
  }
  if (!closestBlockLeft && closestBlockRight) {
    return closestBlockRight;
  }
  if (!closestBlockLeft && !closestBlockRight) {
    return std::unique_ptr<fb::Point>();
  }

  int deltax = column - closestBlockLeft->x;
  int deltay = closestBlockRight->x - column;

  if (deltax > deltay) {
    return closestBlockRight;
  }
  if (deltay > deltax) {
    return closestBlockLeft;
  }
  return closestBlockLeft;
}

std::unique_ptr<fb::Point> PanelHelper::getClosestBlock(int column, int row) {
  // First check on the left
  auto closestBlockLeft = std::unique_ptr<fb::Point>();

  for (int x = column - 1; x >= 0; x--) {
    auto&& current = panel.blocks[x][row];
    // If the block is null, just continue
    if (!current) {
      continue;
    }
    // If the blocks are not switchable for any reason, just break
    if (!isBlockSwitchPossible(x, row)) {
      break;
    }
    closestBlockLeft.reset(new fb::Point(x, row));
    break;
  }

  // Then check on the right
  auto closestBlockRight = std::unique_ptr<fb::Point>();

  for (int x = column; x < panel.X - 1; x++) {
    auto&& current = panel.blocks[x + 1][row];
    // If the block is null, just continue
    if (!current) {
      continue;
    }
    // If the blocks are not switchable for any reason, just break
    if (!isBlockSwitchPossible(x, row)) {
      break;
    }
    closestBlockRight.reset(new fb::Point(x, row));
    break;
  }

  if (closestBlockLeft && !closestBlockRight) {
    return closestBlockLeft;
  }
  if (!closestBlockLeft && closestBlockRight) {
    return closestBlockRight;
  }
  if (!closestBlockLeft && !closestBlockRight) {
    return std::unique_ptr<fb::Point>();
  }

  int deltax = column - closestBlockLeft->x;
  int deltay = closestBlockRight->x - column;

  if (deltax > deltay) {
    return closestBlockRight;
  }
  if (deltay > deltax) {
    return closestBlockLeft;
  }
  return closestBlockLeft;
}
