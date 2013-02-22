//
// Created by bquenin on 9/2/12.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __NonLoopingAnimation_H_
#define __NonLoopingAnimation_H_

#include <iostream>
#include "Animation.h"

class NonLoopingAnimation : Animation {
public:
  int64_t creationTick;

  NonLoopingAnimation(int64_t creationTick, float frameDuration, std::initializer_list<cocos2d::CCSpriteFrame*> frames);
  cocos2d::CCSpriteFrame* getKeyFrame(int64_t stateTick);
  bool isAnimationFinished(int64_t stateTick);
};

#endif //__NonLoopingAnimation_H_
