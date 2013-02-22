//
// Created by bquenin on 2/22/13.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __Garbage_H_
#define __Garbage_H_

#include <iostream>
#include "BlockBar.h"
#include "Combo.h"
#include "Clearing.h"


class Garbage : public BlockBar {
public:
  Garbage(Panel& __parent, int32_t width, int32_t height, int32_t owner, bool skill);

  bool isSkill();
  int32_t getOwner();
  void blink(std::shared_ptr<Combo> combo);
  int32_t reveal(int32_t xOrigin, int32_t yOrigin, int32_t revealingTime, Clearing& parentClearing);
  void inject(int32_t x, int32_t y);
  void onDoneRevealing();

  bool skill;
  std::shared_ptr<Combo> triggeringCombo;
};

#endif //__Garbage_H_
