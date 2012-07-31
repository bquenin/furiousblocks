#include <cstdint>
#include <set>
#include "Clearing.h"

void Clearing::addBlockBar(Panel::BlockBar *bar) {
  for (auto block: bar->barBlocks) {
    block->setClearing(this);
  }
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

bool Clearing::contains(Block *block) {
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

void Clearing::removeBar(Panel::BlockBar *bar) {
  for (auto block: bar->barBlocks) {
    block->setClearing(nullptr);
  }
  bars.erase(bar);
}

void Clearing::setRevealingTime(int64_t revealingTime) {
  this->revealingTime = revealingTime;
}
