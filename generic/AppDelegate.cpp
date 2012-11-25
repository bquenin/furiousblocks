//
//  testAppDelegate.cpp
//  test
//
//  Created by Bertrand Quenin on 01/07/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "CCBReader/CCBReader.h"
#include "SimpleAudioEngine.h"
#include "SceneConstants.h"
#include "PanelScene.h"
#include "TutorialScene.h"
#include "TitleScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
  // Initialize Audio Engine
  SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("harmonic.mp3"));
  SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("gameover.mp3"));
  SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("tutorial.mp3"));
  SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);

  // initialize director
  CCDirector *pDirector = CCDirector::sharedDirector();
  CCEGLView *pEGLView = CCEGLView::sharedOpenGLView();

  pDirector->setOpenGLView(pEGLView);

  // Set the design resolution
  pEGLView->setDesignResolutionSize(SceneConstants::designResolutionSize.width, SceneConstants::designResolutionSize.height, kResolutionExactFit);

  // turn on display FPS
  pDirector->setDisplayStats(true);

  // set FPS. the default value is 1.0/60 if you don't call this
  pDirector->setAnimationInterval(1.0 / 60);

  // run
  pDirector->runWithScene(TitleScene::scene());

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
