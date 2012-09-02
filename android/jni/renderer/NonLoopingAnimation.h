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
  float creationTime;

  NonLoopingAnimation(float creationTime, float frameDuration, std::initializer_list<cocos2d::CCSpriteFrame *> frames);
  cocos2d::CCSpriteFrame *getKeyFrame(float stateTime);
  bool isAnimationFinished(float stateTime);
};

#endif //__NonLoopingAnimation_H_
