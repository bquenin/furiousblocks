//
// Created by bquenin on 11/2/12.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __AbstractPanelScene_H_
#define __AbstractPanelScene_H_

#include <iostream>
#include "Animation.h"
#include "Combo.h"
#include "FuriousBlocksCore.h"
#include "NonLoopingAnimation.h"
#include "tweener_group.hpp"
#include "cocos2d.h"

using namespace cocos2d;
using namespace claw::tween;

class AbstractPanelScene : public cocos2d::CCLayer {
public:
  static constexpr int32_t xOffset = 34;
  static constexpr int32_t yOffset = -76;

  AbstractPanelScene();
  ~AbstractPanelScene();
  bool init();

  // Core
  FuriousBlocksCore *core;
  bool gameRunning;
  int64_t tick;

  // Renderer
  float stateTime;
  CCSpriteBatchNode *batch;
  CCSprite *grid[FuriousBlocksCoreDefaults::PANEL_WIDTH][FuriousBlocksCoreDefaults::PANEL_HEIGHT + 1];
#if DEBUG
  CCLabelTTF *debug[FuriousBlocksCoreDefaults::PANEL_WIDTH][FuriousBlocksCoreDefaults::PANEL_HEIGHT + 1];
#endif
  tweener_group tweeners;
};

#endif //__AbstractPanelScene_H_
