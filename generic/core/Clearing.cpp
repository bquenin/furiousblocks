//
// Created by bquenin on 2/22/13.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "Clearing.h"

void Clearing::addBlockBar(std::shared_ptr<BlockBar> bar) {
//  for (auto &block: bar->barBlocks) {
//    block->clearing = this;
//  }
  bars.insert(bar);
}

bool Clearing::isDoneRevealing(int64_t tick) {
  return tick == revealingTime;
}

void Clearing::onDoneRevealing() {
  for (auto bar: bars) {
    bar->onDoneRevealing();
  }
}

bool Clearing::contains(std::shared_ptr<fb::Block> block) {
  for (auto bar: bars) {
    if (bar->contains(block)) {
      return true;
    }
  }
  return false;
}

bool Clearing::isEmpty() {
  return bars.empty();
}

void Clearing::removeBar(std::shared_ptr<BlockBar> bar) {
//  for (auto block : bar->barBlocks) {
//    block->clearing = nullptr;
//  }
  bars.erase(bar);
}

void Clearing::setRevealingTime(int64_t revealingTime) {
  this->revealingTime = revealingTime;
}
