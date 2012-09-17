//
// Created by bquenin on 9/2/12.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "NonLoopingAnimation.h"

NonLoopingAnimation::NonLoopingAnimation(int64_t creationTick, float frameDuration, std::initializer_list<cocos2d::CCSpriteFrame *> frames)
: Animation(frameDuration, frames)
, creationTick(creationTick) {
}

cocos2d::CCSpriteFrame *NonLoopingAnimation::getKeyFrame(int64_t stateTick) {
  return Animation::getKeyFrame(stateTick - creationTick, false);
}

bool NonLoopingAnimation::isAnimationFinished(int64_t stateTick) {
  return Animation::isAnimationFinished(stateTick - creationTick);
}