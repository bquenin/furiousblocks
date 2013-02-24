//
// Created by bquenin on 2/24/13.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "PanelHelper.h"

bool PanelHelper::isBlockSwitchPossible(int x, int y) const {
  return fb::Block::isMovable(panel.blocks[x][y].get()) && fb::Block::isMovable(panel.blocks[x + 1][y].get());
}
