//
//  testAppDelegate.cpp
//  test
//
//  Created by Bertrand Quenin on 01/07/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

#include "AppDelegate.h"

#include "LogoScene.h"
#include "Poco/Net/SSLManager.h"
#include "PanelScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

Assets AppDelegate::assets;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
  // Initialize SSL
  Poco::Net::initializeSSL();

  // seed for random
  srand(static_cast<unsigned int>(time(NULL)));

  // initialize director
  CCDirector* pDirector = CCDirector::sharedDirector();
  pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

  // Set the design resolution
  pDirector->getOpenGLView()->setDesignResolutionSize(Assets::designResolutionSize.width, Assets::designResolutionSize.height, kResolutionExactFit);

  // set FPS. the default value is 1.0/60 if you don't call this
  pDirector->setAnimationInterval(1.0 / 60);

  // Set volume
  if (AppDelegate::isMusicOn()) {
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1);
  } else {
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
  }

  // Loading assets
  assets.load();

  // run
  pDirector->runWithScene(LogoScene::scene());
//  pDirector->runWithScene(PanelScene::scene());

  return true;
}

// This function will be called when the app is inactive. When comes a phone call, it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
  CCLOG("AppDelegate::applicationDidEnterBackground()");
  // if you use SimpleAudioEngine, it must be pause
  SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();

  CCDirector::sharedDirector()->pause();

  CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
  CCLOG("AppDelegate::applicationWillEnterForeground()");

  CCDirector::sharedDirector()->resume();

  CCTextureCache::sharedTextureCache()->reloadAllTextures();

  // if you use SimpleAudioEngine, it must resume here
  SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

bool AppDelegate::isMusicOn() {
  return CCUserDefault::sharedUserDefault()->getBoolForKey("musicOn", true);
}

void AppDelegate::setMusicOn(bool musicOn) {
  CCUserDefault::sharedUserDefault()->setBoolForKey("musicOn", musicOn);
  CCUserDefault::sharedUserDefault()->flush();
}

bool AppDelegate::isLoggedIn() {
  return CCUserDefault::sharedUserDefault()->getBoolForKey("loggedIn", false);
}

void AppDelegate::setLoggedIn(bool loggedIn) {
  CCUserDefault::sharedUserDefault()->setBoolForKey("loggedIn", loggedIn);
  CCUserDefault::sharedUserDefault()->flush();
}

std::string AppDelegate::getAccessToken() {
  return CCUserDefault::sharedUserDefault()->getStringForKey("accessToken", "none");
}

void AppDelegate::setAccessToken(const std::string& accessToken) {
  CCUserDefault::sharedUserDefault()->setStringForKey("accessToken", accessToken);
  CCUserDefault::sharedUserDefault()->flush();
}

std::string AppDelegate::getFacebookId() {
  return CCUserDefault::sharedUserDefault()->getStringForKey("facebookId", "none");
}

void AppDelegate::setFacebookId(const std::string& facebookId) {
  CCUserDefault::sharedUserDefault()->setStringForKey("facebookId", facebookId);
  CCUserDefault::sharedUserDefault()->flush();
}

std::string AppDelegate::getFirstName() {
  return CCUserDefault::sharedUserDefault()->getStringForKey("firstName", "none");
}

void AppDelegate::setFirstName(const std::string& firstName) {
  CCUserDefault::sharedUserDefault()->setStringForKey("firstName", firstName);
  CCUserDefault::sharedUserDefault()->flush();
}

std::string AppDelegate::getLastName() {
  return CCUserDefault::sharedUserDefault()->getStringForKey("lastName", "none");
}

void AppDelegate::setLastName(const std::string& lastName) {
  CCUserDefault::sharedUserDefault()->setStringForKey("lastName", lastName);
  CCUserDefault::sharedUserDefault()->flush();
}


