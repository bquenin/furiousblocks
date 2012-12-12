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

  musicSwitchOn = CCControlButton::create(CCLabelTTF::create("Music: On", "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
  musicSwitchOn->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  musicSwitchOn->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  musicSwitchOn->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 - 120));
  musicSwitchOn->setPreferredSize(CCSizeMake(musicSwitchOn->getContentSize().width + 20, 60));
  musicSwitchOn->addTargetWithActionForControlEvents(this, cccontrol_selector(PanelMenuOverlay::musicSwitchAction), CCControlEventTouchUpInside);
  musicSwitchOn->setVisible(AppDelegate::musicOn);
  addChild(musicSwitchOn);

  musicSwitchOff = CCControlButton::create(CCLabelTTF::create("Music: Off", "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
  musicSwitchOff->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  musicSwitchOff->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  musicSwitchOff->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 - 120));
  musicSwitchOff->setPreferredSize(CCSizeMake(musicSwitchOff->getContentSize().width + 20, 60));
  musicSwitchOff->addTargetWithActionForControlEvents(this, cccontrol_selector(PanelMenuOverlay::musicSwitchAction), CCControlEventTouchUpInside);
  musicSwitchOff->setVisible(!AppDelegate::musicOn);
  addChild(musicSwitchOff);

  setVisible(false);

  return true;
}

void PanelScene::setVisible(bool visible) {
  CCNode::setVisible(visible);

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

void PanelMenuOverlay::musicSwitchAction(CCObject *sender) {
  AppDelegate::musicOn = !AppDelegate::musicOn;
  musicSwitchOn->setVisible(AppDelegate::musicOn);
  musicSwitchOff->setVisible(!AppDelegate::musicOn);
  if (AppDelegate::musicOn) {
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1);
  } else {
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
  }
}
