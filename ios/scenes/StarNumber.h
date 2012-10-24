//
// Created by bquenin on 10/8/12.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __StarNumber_H_
#define __StarNumber_H_

#include <iostream>
#include "cocos2d.h"
#include "tweener_group.hpp"
#include "single_tweener.hpp"
#include "PanelScene.h"

using namespace cocos2d;

class PanelScene;

class StarNumber {
public:
  StarNumber(PanelScene *panelScene, int32_t x, int32_t y, std::string label, ccColor3B color);
  void onTweenFinished();

  PanelScene *panelScene;
  CCSprite *ccSprite;
  CCLabelBMFont *ccLabel;
  claw::tween::tweener_group tweener;
};

#endif //__StarNumber_H_