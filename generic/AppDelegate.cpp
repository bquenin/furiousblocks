//
//  testAppDelegate.cpp
//  test
//
//  Created by Bertrand Quenin on 01/07/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "PanelScene.h"

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
  srand(time(NULL));

  // initialize director
  CCDirector *pDirector = CCDirector::sharedDirector();
  pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

  // Set the design resolution
  pDirector->getOpenGLView()->setDesignResolutionSize(Assets::designResolutionSize.width, Assets::designResolutionSize.height, kResolutionExactFit);

  // turn on display FPS
  // pDirector->setDisplayStats(true);

  // set FPS. the default value is 1.0/60 if you don't call this
  pDirector->setAnimationInterval(1.0 / 60);

  // Loading assets
  assets.load();

  // run
  pDirector->runWithScene(PanelScene::scene());

  return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
  CCDirector::sharedDirector()->pause();

  // if you use SimpleAudioEngine, it must be pause
  SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
  CCDirector::sharedDirector()->resume();

  // if you use SimpleAudioEngine, it must resume here
  SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
