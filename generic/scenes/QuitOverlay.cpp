//
// Created by bquenin on 11/12/12.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "QuitOverlay.h"
#include "TitleScene.h"
#include "Assets.h"
#include "AppDelegate.h"

using namespace cocos2d;

QuitOverlay::QuitOverlay() {
}

bool QuitOverlay::init() {
  if (!CCLayer::init()) {
    return false;
  }

  initWithColor(ccc4(0, 0, 0, 80));

  resumeButton = CCControlButton::create(CCLabelTTF::create("Continue", "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
  resumeButton->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  resumeButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  resumeButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 + 40));
  resumeButton->setPreferredSize(CCSizeMake(resumeButton->getContentSize().width + 20, 60));
  resumeButton->addTargetWithActionForControlEvents(this, cccontrol_selector(QuitOverlay::resumeAction), CCControlEventTouchUpInside);
  addChild(resumeButton);

  skipButton = CCControlButton::create(CCLabelTTF::create("End tutorial", "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
  skipButton->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  skipButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  skipButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 - 40));
  skipButton->setPreferredSize(CCSizeMake(skipButton->getContentSize().width + 20, 60));
  skipButton->addTargetWithActionForControlEvents(this, cccontrol_selector(QuitOverlay::skipAction), CCControlEventTouchUpInside);
  addChild(skipButton);

  setVisible(false);

  return true;
}

void QuitOverlay::resumeAction(CCObject *sender) {
  setVisible(false);
}

void QuitOverlay::skipAction(CCObject *sender) {
  CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::create(Assets::transitionDuration, TitleScene::scene(), kOrientationUpOver));
}
