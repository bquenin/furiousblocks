#include <cstdint>
#include "Clearing.h"

using namespace std;

void Clearing::addBlockBar(Panel::BlockBar* bar) {
  for (auto block: bar->barBlocks) {
    block->clearing = this;
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

bool Clearing::contains(Block& block) {
  for (auto bar: bars) {
    if (bar->contains(block)) {
      return true;
    }
  }
  return false;
}

bool Clearing::isEmpty() {
  return bars.size() == 0;
}

void Clearing::removeBar(Panel::BlockBar* bar) {
  for (auto block: bar->barBlocks) {
    block->clearing = nullptr;
  }
  bars.erase(bar);
}

void Clearing::setRevealingTime(int64_t revealingTime) {
  this->revealingTime = revealingTime;
}
