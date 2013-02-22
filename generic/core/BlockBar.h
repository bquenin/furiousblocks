//
// Created by bquenin on 2/22/13.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __BlockBar_H_
#define __BlockBar_H_

#include <iostream>
#include <unordered_set>
#include "Block.h"

class Panel;

class BlockBar {
public:
  BlockBar(Panel& __parent, int32_t width, int32_t height, int32_t owner);

  bool contains(std::shared_ptr<fb::Block> block);
  bool hasToFall(int32_t xOrigin, int32_t yOrigin);
  void fall(int32_t xOrigin, int32_t yOrigin);
  void idle();
  void blink();
  bool isRevealing();

  virtual void onDoneRevealing() = 0;

  Panel& panel;
  int32_t id;
  int32_t owner;
  int32_t width;
  int32_t height;
  std::unordered_set<std::shared_ptr<fb::Block>> barBlocks;
};

#endif //__BlockBar_H_
