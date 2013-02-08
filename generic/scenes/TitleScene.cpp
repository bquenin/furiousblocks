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
#include "ScoresScene.h"

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

  logIn = CCControlButton::create(CCLabelTTF::create("   Log in", "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
  logIn->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  logIn->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  logIn->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 + 120));
  logIn->setPreferredSize(CCSizeMake(logIn->getContentSize().width + 20, 60));
  logIn->addTargetWithActionForControlEvents(this, cccontrol_selector(TitleScene::logInAction), CCControlEventTouchUpInside);
  logIn->setVisible(!AppDelegate::isLoggedIn());
  addChild(logIn);

  logOut = CCControlButton::create(CCLabelTTF::create("   Log out", "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
  logOut->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  logOut->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  logOut->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 + 120));
  logOut->setPreferredSize(CCSizeMake(logOut->getContentSize().width + 20, 60));
  logOut->addTargetWithActionForControlEvents(this, cccontrol_selector(TitleScene::logOutAction), CCControlEventTouchUpInside);
  logOut->setVisible(AppDelegate::isLoggedIn());
  addChild(logOut);

  CCSprite *logoLogin = CCSprite::createWithSpriteFrame(AppDelegate::assets.FLOGO);
  logoLogin->setAnchorPoint(ccp(0, 0));
  logoLogin->setPosition(ccp(8, 6));
  logIn->addChild(logoLogin);

  CCSprite *logoLogout = CCSprite::createWithSpriteFrame(AppDelegate::assets.FLOGO);
  logoLogout->setAnchorPoint(ccp(0, 0));
  logoLogout->setPosition(ccp(8, 6));
  logOut->addChild(logoLogout);

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

  scoresButton = CCControlButton::create(CCLabelTTF::create("Scores", "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
  scoresButton->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  scoresButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  scoresButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 - 120));
  scoresButton->setPreferredSize(CCSizeMake(scoresButton->getContentSize().width + 20, 60));
  scoresButton->addTargetWithActionForControlEvents(this, cccontrol_selector(TitleScene::scoresAction), CCControlEventTouchUpInside);
  addChild(scoresButton);

  CCControlButton *creditsButton = CCControlButton::create(CCLabelTTF::create("Credits", "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
  creditsButton->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  creditsButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  creditsButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 - 200));
  creditsButton->setPreferredSize(CCSizeMake(creditsButton->getContentSize().width + 20, 60));
  creditsButton->addTargetWithActionForControlEvents(this, cccontrol_selector(TitleScene::creditsAction), CCControlEventTouchUpInside);
  addChild(creditsButton);

  musicSwitchOn = CCControlButton::create(CCLabelTTF::create("Music: On", "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
  musicSwitchOn->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  musicSwitchOn->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  musicSwitchOn->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 - 280));
  musicSwitchOn->setPreferredSize(CCSizeMake(musicSwitchOn->getContentSize().width + 20, 60));
  musicSwitchOn->addTargetWithActionForControlEvents(this, cccontrol_selector(TitleScene::musicSwitchAction), CCControlEventTouchUpInside);
  musicSwitchOn->setVisible(AppDelegate::isMusicOn());
  addChild(musicSwitchOn);

  musicSwitchOff = CCControlButton::create(CCLabelTTF::create("Music: Off", "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
  musicSwitchOff->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  musicSwitchOff->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  musicSwitchOff->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 - 280));
  musicSwitchOff->setPreferredSize(CCSizeMake(musicSwitchOff->getContentSize().width + 20, 60));
  musicSwitchOff->addTargetWithActionForControlEvents(this, cccontrol_selector(TitleScene::musicSwitchAction), CCControlEventTouchUpInside);
  musicSwitchOff->setVisible(!AppDelegate::isMusicOn());
  addChild(musicSwitchOff);

  CCControlButton *quitButton = CCControlButton::create(CCLabelTTF::create("Quit", "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
  quitButton->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  quitButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  quitButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 - 360));
  quitButton->setPreferredSize(CCSizeMake(quitButton->getContentSize().width + 20, 60));
  quitButton->addTargetWithActionForControlEvents(this, cccontrol_selector(TitleScene::quitAction), CCControlEventTouchUpInside);
  addChild(quitButton);

  CCLabelTTF *copyright = CCLabelTTF::create("Copyright 2013 PixodromE", "SkaterDudes.ttf", 32);
  copyright->setPosition(ccp(Assets::designResolutionSize.width / 2, 32 ));
  copyright->setColor(ccc3(10, 10, 10));
  addChild(copyright);

  // Start scheduling
  schedule(schedule_selector(TitleScene::update));

  return true;
}

void TitleScene::update(float dt) {
  logIn->setVisible(!AppDelegate::isLoggedIn());
  logOut->setVisible(AppDelegate::isLoggedIn());

  scoresButton->setEnabled(AppDelegate::isLoggedIn());
  scoresButton->setColor(AppDelegate::isLoggedIn() ? ccc3(0xFF, 0xFF, 0xFF) : ccc3(0x80, 0x80, 0x80));
}

void TitleScene::logInAction(CCObject *sender) {
  AppDelegate::facebookLogin();
}

void TitleScene::logOutAction(CCObject *sender) {
  AppDelegate::facebookLogout();
}

void TitleScene::playAction(CCObject *sender) {
  CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::create(Assets::transitionDuration, PanelScene::scene(), kOrientationUpOver));
}

void TitleScene::howToPlayAction(CCObject *sender) {
  CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::create(Assets::transitionDuration, TutorialScene::scene(), kOrientationUpOver));
}

void TitleScene::scoresAction(CCObject *sender) {
  CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::create(Assets::transitionDuration, ScoresScene::scene(), kOrientationUpOver));
}

void TitleScene::creditsAction(CCObject *sender) {
  CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::create(Assets::transitionDuration, CreditsScene::scene(), kOrientationUpOver));
}

void TitleScene::musicSwitchAction(CCObject *sender) {
  AppDelegate::setMusicOn(!AppDelegate::isMusicOn());
  musicSwitchOn->setVisible(AppDelegate::isMusicOn());
  musicSwitchOff->setVisible(!AppDelegate::isMusicOn());
  if (AppDelegate::isMusicOn()) {
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1);
  } else {
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
  }
}

void TitleScene::quitAction(CCObject *sender) {
  AppDelegate::quit();
}
