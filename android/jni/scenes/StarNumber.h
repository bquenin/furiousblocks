//
// Created by bquenin on 10/8/12.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __StarNumber_H_
#define __StarNumber_H_

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class StarNumber {
public:
  StarNumber(int32_t x, int32_t y, std::string label, ccColor3B color);
  CCSprite *ccSprite;
  CCLabelBMFont *ccLabel;
  //  tween::TweenerParam param;
};

#endif //__StarNumber_H_