#ifndef __Clearing_H_
#define __Clearing_H_

#include <cstdint>
#include <set>
#include "Panel.h"
#include "Block.h"

using namespace std;

class Clearing {
private:
  unordered_set<Panel::BlockBar *> bars;
  int64_t revealingTime = 0;

protected:
public:
  void addBlockBar(Panel::BlockBar* bar);
  bool isDoneRevealing(int64_t tick);
  void onDoneRevealing();
  bool contains(Block& block);
  bool isEmpty();
  void removeBar(Panel::BlockBar* bar);
  void setRevealingTime(int64_t revealingTime);
};

#endif //__Clearing_H_
