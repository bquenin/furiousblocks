//
// Created by bquenin on 9/2/12.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "Animation.h"

Animation::Animation(float frameDuration, std::initializer_list<cocos2d::CCSpriteFrame *> frames)
: frameDuration(frameDuration) {
  for (cocos2d::CCSpriteFrame *frame : frames) {
    keyFrames.push_back(frame);
  }
  animationDuration = frameDuration * keyFrames.size();
}

cocos2d::CCSpriteFrame *Animation::getKeyFrame(float stateTime, bool looping) {
  size_t frameNumber = static_cast<size_t> (stateTime / frameDuration);

  if (!looping) {
    frameNumber = std::min(keyFrames.size() - 1, frameNumber);
  } else {
    frameNumber = frameNumber % keyFrames.size();
  }
  CCLOG("returning frame address = %X", keyFrames[frameNumber]);
  return keyFrames[frameNumber];
}

bool Animation::isAnimationFinished(float stateTime) {
  size_t frameNumber = static_cast<size_t> (stateTime / frameDuration);
  return keyFrames.size() - 1 < frameNumber;
}
