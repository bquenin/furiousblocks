//
// Created by bquenin on 2/24/13.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "PanelHelper.h"

bool PanelHelper::isBlockSwitchPossible(const fb::Point &location) {
  return fb::Block::isMovable(panel.blocks[location.x][location.y].get()) && fb::Block::isMovable(panel.blocks[location.x + 1][location.y].get());
}
