//
// Created by bquenin on 2/22/13.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "BlockBar.h"
#include "Panel.h"

BlockBar::BlockBar(Panel& panel, int32_t width, int32_t height, int32_t owner)
: panel(panel)
, id(panel.random.nextInt())
, width(width)
, height(height >= Panel::Y - Panel::Y_DISPLAY ? Panel::Y - Panel::Y_DISPLAY : height)
, owner(owner) {
}

bool BlockBar::contains(std::shared_ptr<fb::Block> block) {
  return barBlocks.find(block) != barBlocks.end();
}

bool BlockBar::hasToFall(int32_t xOrigin, int32_t yOrigin) {
  for (int32_t x = xOrigin; x < xOrigin + width && x < Panel::X; x++) {
    if (panel.blocks[x][yOrigin - 1] != nullptr) {
      return false;
    }
  }
  return true;
}

void BlockBar::fall(int32_t xOrigin, int32_t yOrigin) {
  for (int32_t y = yOrigin; y < yOrigin + height && y < Panel::Y; y++) {
    for (int32_t x = xOrigin; x < xOrigin + width && x < Panel::X; x++) {
      panel.blocks[x][y - 1] = panel.blocks[x][y];
      panel.blocks[x][y].reset();
    }
  }
}

void BlockBar::idle() {
  for (auto block: barBlocks) {
    block->idle();
  }
}

void BlockBar::blink() {
  auto first = barBlocks.begin();
  if ((*first)->state == BlockState::BLINKING) {
    return;
  }
  //  if (barBlocks->iterator()->next()->state == BlockState::BLINKING) {
  //    return poppingIndex;
  //  }
  for (auto block: barBlocks) {
    block->blink();
  }
}

bool BlockBar::isRevealing() {
  for (auto block: barBlocks) {
    if (block->state == BlockState::REVEALING) {
      return true;
    }
  }
  return false;
}

