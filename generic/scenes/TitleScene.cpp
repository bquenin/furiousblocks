//
// Created by tsug on 04/07/12.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "TitleScene.h"
#include "TutorialScene.h"
#include "PanelScene.h"
#include "SimpleAudioEngine.h"
#include "Assets.h"
#include "AppDelegate.h"
#include "CreditsScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene *TitleScene::scene() {
  CCScene *scene = CCScene::create();
  scene->addChild(TitleScene::create());
  return scene;
}

bool TitleScene::init() {
  if (!CCLayer::init()) {
    return false;
  }

  // Start music
  SimpleAudioEngine::sharedEngine()->playBackgroundMusic("harmonic.mp3", true);

  // Background
  CCSprite *bg = CCSprite::createWithSpriteFrame(AppDelegate::assets.TITLE);
  bg->setAnchorPoint(ccp(0, 0));
  addChild(bg);

#ifdef FREEMIUM
  CCControlButton *playButton = CCControlButton::create(CCLabelTTF::create(Assets::format("Play! (%d left)", AppDelegate::getGamesLeft()).c_str(), "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
#else
  CCControlButton *playButton = CCControlButton::create(CCLabelTTF::create("Play!", "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
#endif
  playButton->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  playButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  playButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 + 40));
  playButton->setPreferredSize(CCSizeMake(playButton->getContentSize().width + 20, 60));
  playButton->addTargetWithActionForControlEvents(this, cccontrol_selector(TitleScene::playAction), CCControlEventTouchUpInside);
  addChild(playButton);

  CCControlButton *howToPlaylButton = CCControlButton::create(CCLabelTTF::create("How to play", "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
  howToPlaylButton->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  howToPlaylButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  howToPlaylButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 - 40));
  howToPlaylButton->setPreferredSize(CCSizeMake(howToPlaylButton->getContentSize().width + 20, 60));
  howToPlaylButton->addTargetWithActionForControlEvents(this, cccontrol_selector(TitleScene::howToPlayAction), CCControlEventTouchUpInside);
  addChild(howToPlaylButton);

  CCControlButton *creditsButton = CCControlButton::create(CCLabelTTF::create("Credits", "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
  creditsButton->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  creditsButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  creditsButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 - 120));
  creditsButton->setPreferredSize(CCSizeMake(creditsButton->getContentSize().width + 20, 60));
  creditsButton->addTargetWithActionForControlEvents(this, cccontrol_selector(TitleScene::creditsAction), CCControlEventTouchUpInside);
  addChild(creditsButton);

  CCLabelTTF *musicLabel = CCLabelTTF::create("Music", "SkaterDudes.ttf", 32);
  musicLabel->setPosition(ccp(Assets::designResolutionSize.width / 2 - 60, Assets::designResolutionSize.height / 2 - 200));
  addChild(musicLabel);

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
  musicSwitch->setPosition(ccp(Assets::designResolutionSize.width / 2 + 60 , Assets::designResolutionSize.height / 2 - 200));
  musicSwitch->setOn(AppDelegate::musicOn);
  addChild(musicSwitch);

  musicSwitch->addTargetWithActionForControlEvents(this, cccontrol_selector(TitleScene::musicSwitchChanged), CCControlEventValueChanged);

  CCLabelTTF *copyright = CCLabelTTF::create("Copyright 2012 PixodromE", "SkaterDudes.ttf", 32);
  copyright->setPosition(ccp(Assets::designResolutionSize.width / 2, 32 ));
  copyright->setColor(ccc3(10, 10, 10));
  addChild(copyright);

  return true;
}

void TitleScene::playAction(CCObject *sender) {
  CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::create(Assets::transitionDuration, PanelScene::scene(), kOrientationUpOver));
}

void TitleScene::howToPlayAction(CCObject *sender) {
  CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::create(Assets::transitionDuration, TutorialScene::scene(), kOrientationUpOver));
}

void TitleScene::creditsAction(CCObject *sender) {
  CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::create(Assets::transitionDuration, CreditsScene::scene(), kOrientationUpOver));
}

void TitleScene::musicSwitchChanged(CCObject *sender, CCControlEvent controlEvent) {
  CCControlSwitch *pSwitch = (CCControlSwitch *) sender;
  AppDelegate::musicOn = pSwitch->isOn();
  if (AppDelegate::musicOn) {
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1);
  } else {
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
  }
}

