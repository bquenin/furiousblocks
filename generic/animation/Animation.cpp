//
// Created by bquenin on 9/2/12.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "Animation.h"

Animation::Animation(int64_t frameDuration, std::initializer_list<cocos2d::CCSpriteFrame*> frames)
: frameDuration(frameDuration) {
  for (cocos2d::CCSpriteFrame* frame : frames) {
    keyFrames.push_back(frame);
  }
}

cocos2d::CCSpriteFrame* Animation::getKeyFrame(int64_t stateTick, bool looping) {
  size_t frameNumber = static_cast<size_t> (stateTick / frameDuration);

  if (!looping) {
    frameNumber = std::min(keyFrames.size() - 1, frameNumber);
  } else {
    frameNumber = frameNumber % keyFrames.size();
  }
  return keyFrames[frameNumber];
}

bool Animation::isAnimationFinished(int64_t stateTick) {
  size_t frameNumber = static_cast<size_t> (stateTick / frameDuration);
  return keyFrames.size() - 1 < frameNumber;
}
