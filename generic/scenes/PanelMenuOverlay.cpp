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
#include "PanelScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

PanelMenuOverlay::PanelMenuOverlay() {
}

bool PanelMenuOverlay::init() {
  if (!CCLayer::init()) {
    return false;
  }

  initWithColor(ccc4(0, 0, 0, 80));

  continueButton = CCControlButton::create(CCLabelTTF::create("Continue", "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
  continueButton->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  continueButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  continueButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 + 120));
  continueButton->setPreferredSize(CCSizeMake(continueButton->getContentSize().width + 20, 60));
  continueButton->addTargetWithActionForControlEvents(this, cccontrol_selector(PanelMenuOverlay::continueAction), CCControlEventTouchUpInside);
  addChild(continueButton);

#ifdef FREEMIUM
  restartButton = CCControlButton::create(CCLabelTTF::create(Assets::format("Restart (%d left)", AppDelegate::getGamesLeft()).c_str(), "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
#else
  restartButton = CCControlButton::create(CCLabelTTF::create(Assets::format("Restart", AppDelegate::getGamesLeft()).c_str(), "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
#endif
  restartButton->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  restartButton->setTitleColorForState(ccWHITE,CCControlStateHighlighted);
  restartButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 + 40));
  restartButton->setPreferredSize(CCSizeMake(restartButton->getContentSize().width + 20, 60));
  restartButton->addTargetWithActionForControlEvents(this, cccontrol_selector(PanelMenuOverlay::restartAction), CCControlEventTouchUpInside);
  addChild(restartButton);

  endGameButton = CCControlButton::create(CCLabelTTF::create("Back to Title", "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
  endGameButton->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  endGameButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  endGameButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 - 40));
  endGameButton->setPreferredSize(CCSizeMake(endGameButton->getContentSize().width + 20, 60));
  endGameButton->addTargetWithActionForControlEvents(this, cccontrol_selector(PanelMenuOverlay::endGameAction), CCControlEventTouchUpInside);
  addChild(endGameButton);

  CCLabelTTF *musicLabel = CCLabelTTF::create("Music", "SkaterDudes.ttf", 32);
  musicLabel->setPosition(ccp(Assets::designResolutionSize.width / 2 - 60, Assets::designResolutionSize.height / 2 - 120));
  addChild(musicLabel);

  // Create the switch
  CCControlSwitch *musicSwitch = CCControlSwitch::create
      (
          CCSprite::create("switch-mask.png"),
          CCSprite::create("switch-on.png"),
          CCSprite::create("switch-off.png"),
          CCSprite::create("switch-thumb.png"),
          CCLabelTTF::create("On", "SkaterDudes.ttf", 16),
          CCLabelTTF::create("Off", "SkaterDudes.ttf", 16)
      );
  musicSwitch->setScale(1.5);
  musicSwitch->setPosition(ccp(Assets::designResolutionSize.width / 2 + 60 , Assets::designResolutionSize.height / 2 - 120));
  musicSwitch->setOn(AppDelegate::musicOn);
  addChild(musicSwitch);

  musicSwitch->addTargetWithActionForControlEvents(this, cccontrol_selector(PanelMenuOverlay::musicSwitchChanged), CCControlEventValueChanged);

  setVisible(false);

  return true;
}

void PanelMenuOverlay::continueAction(CCObject *sender) {
  setVisible(false);
}

void PanelMenuOverlay::restartAction(CCObject *sender) {
  setVisible(false);
  CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::create(Assets::transitionDuration, PanelScene::scene(), kOrientationUpOver));
}

void PanelMenuOverlay::endGameAction(CCObject *sender) {
  setVisible(false);
  CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::create(Assets::transitionDuration, TitleScene::scene(), kOrientationUpOver));
}

void PanelMenuOverlay::musicSwitchChanged(CCObject *sender, CCControlEvent controlEvent) {
  CCControlSwitch *pSwitch = (CCControlSwitch *) sender;
  AppDelegate::musicOn = pSwitch->isOn();
  if (AppDelegate::musicOn) {
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1);
  } else {
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
  }
}
