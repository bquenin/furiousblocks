//
// Created by bquenin on 11/25/12.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "PanelMenuOverlay.h"

#include "TitleScene.h"
#include "SimpleAudioEngine.h"
#include "Assets.h"
#include "AppDelegate.h"

using namespace cocos2d;
using namespace CocosDenshion;

PanelMenuOverlay::PanelMenuOverlay() {
}

bool PanelMenuOverlay::init() {
  if (!CCLayer::init()) {
    return false;
  }

  initWithColor(ccc4(0, 0, 0, 80));

  /** Creates and return a button with a default background and title color. */
  CCScale9Sprite *skipBackgroundButton = CCScale9Sprite::create("button.png");
  CCScale9Sprite *skipBackgroundHighlightedButton = CCScale9Sprite::create("buttonHighlighted.png");
  EndGameButton = CCControlButton::create(CCLabelTTF::create("Back to Title", "SkaterDudes.ttf", 32), skipBackgroundButton);
  EndGameButton->setBackgroundSpriteForState(skipBackgroundHighlightedButton, CCControlStateHighlighted);
  EndGameButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  EndGameButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 + 40));
  EndGameButton->setPreferredSize(CCSizeMake(EndGameButton->getContentSize().width + 20, 60));
  EndGameButton->addTargetWithActionForControlEvents(this, cccontrol_selector(PanelMenuOverlay::endGameAction), CCControlEventTouchUpInside);
  addChild(EndGameButton);

  CCScale9Sprite *resumeBackgroundButton = CCScale9Sprite::create("button.png");
  CCScale9Sprite *resumeBackgroundHighlightedButton = CCScale9Sprite::create("buttonHighlighted.png");
  resumeButton = CCControlButton::create(CCLabelTTF::create("Continue", "SkaterDudes.ttf", 32), resumeBackgroundButton);
  resumeButton->setBackgroundSpriteForState(resumeBackgroundHighlightedButton, CCControlStateHighlighted);
  resumeButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  resumeButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 - 40));
  resumeButton->setPreferredSize(CCSizeMake(resumeButton->getContentSize().width + 20, 60));
  resumeButton->addTargetWithActionForControlEvents(this, cccontrol_selector(PanelMenuOverlay::resumeAction), CCControlEventTouchUpInside);
  addChild(resumeButton);

  // Create the switch
  CCControlSwitch *musicSwitch = CCControlSwitch::create
      (
          CCSprite::create("switch-mask.png"),
          CCSprite::create("switch-on.png"),
          CCSprite::create("switch-off.png"),
          CCSprite::create("switch-thumb.png"),
          CCLabelTTF::create("On", "SkaterDudes.ttf", 32),
          CCLabelTTF::create("Off", "SkaterDudes.ttf", 32)
      );
  musicSwitch->setPosition(ccp(Assets::designResolutionSize.width / 2 + 60, Assets::designResolutionSize.height / 2 - 120));
  musicSwitch->setOn(AppDelegate::musicOn);
  addChild(musicSwitch);

  musicSwitch->addTargetWithActionForControlEvents(this, cccontrol_selector(PanelMenuOverlay::valueChanged), CCControlEventValueChanged);

  setVisible(false);

  return true;
}

void PanelMenuOverlay::endGameAction(CCObject *sender) {
  CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::create(Assets::transitionDuration, TitleScene::scene(), kOrientationUpOver));
}

void PanelMenuOverlay::resumeAction(CCObject *sender) {
  setVisible(false);
}

void PanelMenuOverlay::valueChanged(CCObject *sender, CCControlEvent controlEvent) {
  CCControlSwitch *pSwitch = (CCControlSwitch *) sender;
  AppDelegate::musicOn = pSwitch->isOn();
  if (AppDelegate::musicOn) {
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1);
  } else {
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
  }
}
