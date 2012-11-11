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
#include "CCNodeLoaderLibrary.h"
#include "TitleSceneLoader.h"
#include "PanelScene.h"
#include "SceneConstants.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
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

      /* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary *ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();

    ccNodeLoaderLibrary->registerCCNodeLoader("TitleScene", TitleSceneLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader *ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();

    // create a scene. it's an autorelease object
    CCScene *pScene = CCScene::create();

    /* Read the ccbi file. */
    CCNode *node = ccbReader->readNodeGraphFromFile("TitleScene.ccbi", pScene);

    if (node != NULL) {
      pScene->addChild(node);
    }

    // run
    pDirector->runWithScene(pScene);

//  // create a scene. it's an autorelease object
//  CCScene *pScene = PanelScene::scene();
//
//  // run
//  pDirector->runWithScene(pScene);

  SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("harmonic.mp3"));
  SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("gameover.mp3"));
  SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("tutorial.mp3"));

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
