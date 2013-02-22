//
// Created by bquenin on 2/22/13.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __Clearing_H_
#define __Clearing_H_

#include <iostream>
#include <set>
#include "BlockBar.h"

class Clearing {
public:
  void addBlockBar(std::shared_ptr<BlockBar> bar);
  bool isDoneRevealing(int64_t tick);
  void onDoneRevealing();
  bool contains(std::shared_ptr<fb::Block> block);
  bool isEmpty();
  void removeBar(std::shared_ptr<BlockBar> bar);
  void setRevealingTime(int64_t revealingTime);

  std::set<std::shared_ptr<BlockBar>> bars;
  int64_t revealingTime;
};

#endif //__Clearing_H_
