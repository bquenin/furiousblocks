//
// Created by bquenin on 2/22/13.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __BlockLine_H_
#define __BlockLine_H_

#include <iostream>
#include "BlockBar.h"

class BlockLine : public BlockBar {
public:
  BlockLine(Panel& panel, int32_t width, int32_t owner);

  int32_t reveal(int32_t xOrigin, int32_t yOrigin, int32_t revealingTime);
  void inject(int32_t x, int32_t y);
  void onDoneRevealing();
};

#endif //__BlockLine_H_
