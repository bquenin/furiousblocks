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
      // Same blocks on this line
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
  auto comboStarter = std::unique_ptr<fb::Point>();

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
          comboStarter.reset(new fb::Point(x, line));
          if (helper.isBlockSwitchPossible(*comboStarter)) {
            return std::move(comboStarter);
          }
        }
      }
      // check left
      for (int x = i - 2; x >= 0; x--) {
        if (mask[x]) {
          comboStarter.reset(new fb::Point(x, line));
          if (helper.isBlockSwitchPossible(*comboStarter)) {
            return std::move(comboStarter);
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
          comboStarter.reset(new fb::Point(x, line));
          if (helper.isBlockSwitchPossible(*comboStarter)) {
            return std::move(comboStarter);
          }
        }
      }
      // check left
      for (int x = i - 2; x >= 0; x--) {
        if (mask[x]) {
          comboStarter.reset(new fb::Point(x, line));
          if (helper.isBlockSwitchPossible(*comboStarter)) {
            return std::move(comboStarter);
          }
        }
      }
    }
  }
  return std::move(comboStarter);
}
