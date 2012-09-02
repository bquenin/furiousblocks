//
// Created by bquenin on 9/2/12.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __Animation_H_
#define __Animation_H_

#include <iostream>
#include <vector>
#include "cocos2d.h"

class Animation {
public:
  std::vector<cocos2d::CCSpriteFrame *> keyFrames;
  float frameDuration;
  float animationDuration;
  Animation(float frameDuration, std::initializer_list<cocos2d::CCSpriteFrame *> keyFrames);

  cocos2d::CCSpriteFrame *getKeyFrame(float stateTime, bool looping);
  bool isAnimationFinished(float stateTime);
};

#endif //__Animation_H_
