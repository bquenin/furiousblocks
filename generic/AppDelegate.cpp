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

using namespace cocos2d;
using namespace CocosDenshion;

Assets AppDelegate::assets;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
  Poco::Net::initializeSSL();

  // seed for random
  srand(static_cast<unsigned int>(time(NULL)));

  // initialize director
  CCDirector *pDirector = CCDirector::sharedDirector();
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

  return true;
}

// This function will be called when the app is inactive. When comes a phone call, it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
  CCDirector::sharedDirector()->pause();

  CCTextureCache::sharedTextureCache()->removeUnusedTextures();

  // if you use SimpleAudioEngine, it must be pause
  SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
  getGamesLeft();

  CCDirector::sharedDirector()->resume();

  CCTextureCache::sharedTextureCache()->reloadAllTextures();

  // if you use SimpleAudioEngine, it must resume here
  SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

int32_t AppDelegate::getGamesLeft() {
  int32_t gamesLeft = CCUserDefault::sharedUserDefault()->getIntegerForKey("left", 0);

  // Cheating ?
  if (gamesLeft > 5) {
    gamesLeft = 0;
  }

  // New day ? If so, reset the number of left games
  time_t t = time(0); // get time now
  struct tm *now = localtime(&t);
  if (CCUserDefault::sharedUserDefault()->getIntegerForKey("lastDay", 1) != now->tm_yday) {
    // Update the last day
    CCUserDefault::sharedUserDefault()->setIntegerForKey("lastDay", now->tm_yday);
    CCUserDefault::sharedUserDefault()->flush();
    gamesLeft = 5;
  }

  setGamesLeft(gamesLeft);
  return gamesLeft;
}

void AppDelegate::setGamesLeft(int32_t gamesLeft) {
  CCUserDefault::sharedUserDefault()->setIntegerForKey("left", gamesLeft);
  CCUserDefault::sharedUserDefault()->flush();
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

void AppDelegate::setAccessToken(const std::string accessToken) {
  CCUserDefault::sharedUserDefault()->setStringForKey("accessToken", accessToken);
  CCUserDefault::sharedUserDefault()->flush();
}

