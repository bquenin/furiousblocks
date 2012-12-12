//
//  testAppDelegate.cpp
//  test
//
//  Created by Bertrand Quenin on 01/07/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

#include "AppDelegate.h"

#include "LogoScene.h"
#include "AdScene.h"
#include "TitleScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

bool AppDelegate::musicOn = true;
Assets AppDelegate::assets;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
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
  SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);

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
  // Set number of games to 5 by default
  int32_t gamesLeft = CCUserDefault::sharedUserDefault()->getIntegerForKey("left", 0);

  // Cheating ?
  if (gamesLeft > 5) {
    gamesLeft = 0;
  }

  // New day ? If so, reset the number of left games
  time_t t = time(0); // get time now
  struct tm * now = localtime( & t );
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
