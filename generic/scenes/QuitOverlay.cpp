//
// Created by bquenin on 11/12/12.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "QuitOverlay.h"
#include "TitleScene.h"
#include "Assets.h"

using namespace cocos2d;

QuitOverlay::QuitOverlay() {
}

bool QuitOverlay::init() {
  if (!CCLayer::init()) {
    return false;
  }

  initWithColor(ccc4(0, 0, 0, 80));

  /** Creates and return a button with a default background and title color. */
  CCScale9Sprite *skipBackgroundButton = CCScale9Sprite::create("button.png");
  CCScale9Sprite *skipBackgroundHighlightedButton = CCScale9Sprite::create("buttonHighlighted.png");
  skipButton = CCControlButton::create(CCLabelTTF::create("End tutorial", "SkaterDudes.ttf", 32), skipBackgroundButton);
  skipButton->setBackgroundSpriteForState(skipBackgroundHighlightedButton, CCControlStateHighlighted);
  skipButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  skipButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 + 40));
  skipButton->setPreferredSize(CCSizeMake(skipButton->getContentSize().width + 20, 60));
  skipButton->addTargetWithActionForControlEvents(this, cccontrol_selector(QuitOverlay::skipAction), CCControlEventTouchUpInside);
  addChild(skipButton);

  CCScale9Sprite *resumeBackgroundButton = CCScale9Sprite::create("button.png");
  CCScale9Sprite *resumeBackgroundHighlightedButton = CCScale9Sprite::create("buttonHighlighted.png");
  resumeButton = CCControlButton::create(CCLabelTTF::create("Continue", "SkaterDudes.ttf", 32), resumeBackgroundButton);
  resumeButton->setBackgroundSpriteForState(resumeBackgroundHighlightedButton, CCControlStateHighlighted);
  resumeButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  resumeButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 - 40));
  resumeButton->setPreferredSize(CCSizeMake(resumeButton->getContentSize().width + 20, 60));
  resumeButton->addTargetWithActionForControlEvents(this, cccontrol_selector(QuitOverlay::resumeAction), CCControlEventTouchUpInside);
  addChild(resumeButton);

  setVisible(false);

  return true;
}

void QuitOverlay::skipAction(CCObject *sender) {
  CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::create(Assets::transitionDuration, TitleScene::scene(), kOrientationUpOver));
}

void QuitOverlay::resumeAction(CCObject *sender) {
  setVisible(false);
}
