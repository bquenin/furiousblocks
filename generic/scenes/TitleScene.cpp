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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include "me_pixodro_FuriousBlocks.h"
#endif

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

  CCControlButton *creditsButton = CCControlButton::create(CCLabelTTF::create("Credits", "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
  creditsButton->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  creditsButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  creditsButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 - 120));
  creditsButton->setPreferredSize(CCSizeMake(creditsButton->getContentSize().width + 20, 60));
  creditsButton->addTargetWithActionForControlEvents(this, cccontrol_selector(TitleScene::creditsAction), CCControlEventTouchUpInside);
  addChild(creditsButton);

  musicSwitchOn = CCControlButton::create(CCLabelTTF::create("Music: On", "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
  musicSwitchOn->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  musicSwitchOn->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  musicSwitchOn->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 - 200));
  musicSwitchOn->setPreferredSize(CCSizeMake(musicSwitchOn->getContentSize().width + 20, 60));
  musicSwitchOn->addTargetWithActionForControlEvents(this, cccontrol_selector(TitleScene::musicSwitchAction), CCControlEventTouchUpInside);
  musicSwitchOn->setVisible(AppDelegate::isMusicOn());
  addChild(musicSwitchOn);

  musicSwitchOff = CCControlButton::create(CCLabelTTF::create("Music: Off", "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
  musicSwitchOff->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  musicSwitchOff->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  musicSwitchOff->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 - 200));
  musicSwitchOff->setPreferredSize(CCSizeMake(musicSwitchOff->getContentSize().width + 20, 60));
  musicSwitchOff->addTargetWithActionForControlEvents(this, cccontrol_selector(TitleScene::musicSwitchAction), CCControlEventTouchUpInside);
  musicSwitchOff->setVisible(!AppDelegate::isMusicOn());
  addChild(musicSwitchOff);

  CCControlButton *quitButton = CCControlButton::create(CCLabelTTF::create("Quit", "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
  quitButton->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  quitButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  quitButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 - 280));
  quitButton->setPreferredSize(CCSizeMake(quitButton->getContentSize().width + 20, 60));
  quitButton->addTargetWithActionForControlEvents(this, cccontrol_selector(TitleScene::quitAction), CCControlEventTouchUpInside);
  addChild(quitButton);

  CCLabelTTF *copyright = CCLabelTTF::create("Copyright 2012 PixodromE", "SkaterDudes.ttf", 32);
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
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  exit(0);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
  terminateProcessJNI();
#endif
}

void TitleScene::logInAction(CCObject *sender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  CCApplication::sharedApplication()->onClickLogin();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
  JniMethodInfo minfo;

  if(JniHelper::getStaticMethodInfo(minfo,
    "me/pixodro/FuriousBlocks",
    "onClickLogin",
    "()V"))
  {
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
  }
#endif
}

void TitleScene::logOutAction(CCObject *sender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  CCApplication::sharedApplication()->onClickLogout();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
  JniMethodInfo minfo;

  if(JniHelper::getStaticMethodInfo(minfo,
    "me/pixodro/FuriousBlocks",
    "onClickLogout",
    "()V"))
  {
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    minfo.env->DeleteLocalRef(minfo.classID);
  }
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C" {
  std::string g_sessionStatus("no session status");
  std::string g_accessToken("no access token");

  JNIEXPORT void JNICALL Java_me_pixodro_FuriousBlocks_facebookSessionStatusCallback(JNIEnv *env, jobject thiz, jstring sessionStatus, jstring accessToken) {
    g_sessionStatus = JniHelper::jstring2string(sessionStatus);
    g_accessToken = JniHelper::jstring2string(accessToken);
    std::string OPENED("OPENED");
    AppDelegate::setLoggedIn(g_sessionStatus == OPENED);
//    CCLOG("sessionStatus = %s", g_sessionStatus.c_str());
//    CCLOG("accessToken= %s", g_accessToken.c_str());
  }
}
#endif
