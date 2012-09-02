//
// Created by bquenin on 9/2/12.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "NonLoopingAnimation.h"

NonLoopingAnimation::NonLoopingAnimation(float creationTime, float frameDuration, std::initializer_list<cocos2d::CCSpriteFrame *> frames) : Animation(frameDuration, frames) {
  this->creationTime = creationTime;
}

cocos2d::CCSpriteFrame *NonLoopingAnimation::getKeyFrame(float stateTime) {
  return Animation::getKeyFrame(stateTime - creationTime, false);
}

bool NonLoopingAnimation::isAnimationFinished(float stateTime) {
  return Animation::isAnimationFinished(stateTime - creationTime);
}