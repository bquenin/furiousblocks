//
// Created by bquenin on 2/22/13.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "BlockLine.h"
#include "Panel.h"

BlockLine::BlockLine(Panel& panel, int32_t width, int32_t owner)
: BlockBar(panel, width, 1, owner) {
}

void BlockLine::inject(int32_t x, int32_t y) {
  for (int32_t j = y, h = 0; h < height; j--, h++) {
    for (int32_t i = x, w = 0; w < width; i++, w++) {
      panel.blocks[i][j] = panel.newRandom();
      panel.blocks[i][j]->garbageOwner = owner;
      barBlocks.insert(panel.blocks[i][j]);
    }
  }
}

void BlockLine::onDoneRevealing() {
  for (auto block: barBlocks) {
    block->airBounce();
    block->fallingFromClearing = true;
  }
}

int32_t BlockLine::reveal(int32_t xOrigin, int32_t yOrigin, int32_t revealingTime) {
  if (isRevealing()) {
    return revealingTime;
  }
  int32_t revealingTimeIncrement = revealingTime;
  for (int32_t y = yOrigin; y < yOrigin + height && y < Panel::Y; y++) {
    for (int32_t x = xOrigin; x < xOrigin + width && x < Panel::X; x++) {
      if (y <= Panel::Y_DISPLAY) {
        panel.blocks[x][y]->reveal(revealingTimeIncrement += FuriousBlocksCoreDefaults::BLOCK_REVEALINGTIMEINCREMENT);
      } else {
        panel.blocks[x][y]->reveal(-1);
      }
    }
  }
  return revealingTimeIncrement;
}
