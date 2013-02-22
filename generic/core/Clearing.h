//
// Created by bquenin on 2/22/13.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __Clearing_H_
#define __Clearing_H_

#include <iostream>
#import "Panel.h"

class Clearing {
  friend class Block;

private:
  std::set<std::shared_ptr<Panel::BlockBar>> bars;
  int64_t revealingTime;

protected:
public:
  void addBlockBar(std::shared_ptr<Panel::BlockBar> bar);
  bool isDoneRevealing(int64_t tick);
  void onDoneRevealing();
  bool contains(std::shared_ptr<fb::Block> block);
  bool isEmpty();
  void removeBar(std::shared_ptr<Panel::BlockBar> bar);
  void setRevealingTime(int64_t revealingTime);
};

#endif //__Clearing_H_
