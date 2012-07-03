//
//  testAppDelegate.cpp
//  test
//
//  Created by Bertrand Quenin on 01/07/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "extensions/CCBReader/CCBReader.h"
#include "extensions/CCBReader/CCNodeLoaderLibrary.h"
//#include "HelloCocosBuilder/HelloCocosBuilderLayerLoader.h"

//#include "PanelScene.h"
#include "TitleSceneLoader.h"

USING_NS_CC;
USING_NS_CC_EXT;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
  // initialize director
  CCDirector *pDirector = CCDirector::sharedDirector();
  pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());

  // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
  pDirector->enableRetinaDisplay(true);

  // turn on display FPS
  pDirector->setDisplayStats(true);

  // set FPS. the default value is 1.0/60 if you don't call this
  pDirector->setAnimationInterval(1.0 / 60);

//  // Assume that PVR images have premultiplied alpha
//  [CCTexture2D PVRImagesHavePremultipliedAlpha:YES];
//
//  // Unzip resources published by CocosBuilder
//  [CCBReader unzipResources:@"ccb.zip"];
//
//  // Use the CCBReader to load the HelloCocosBuilder scene
//  // from the ccbi-file.
//  CCScene* scene = [CCBReader sceneWithNodeGraphFromFile:@"HelloCocosBuilder.ccbi"];
//
//  // Add the scene to the stack. The director will run it when it automatically when the view is displayed.
//  [director_ pushScene: scene];


  /* Create an autorelease CCNodeLoaderLibrary. */
  CCNodeLoaderLibrary *ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();

  ccNodeLoaderLibrary->registerCCNodeLoader("TitleScene", TitleSceneLoader::loader());

  /* Create an autorelease CCBReader. */
  cocos2d::extension::CCBReader *ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
  ccbReader->autorelease();

  // create a scene. it's an autorelease object
  CCScene *pScene = CCScene::create();
  CCLOG("scene");
  /* Read the ccbi file. */
  CCNode *node = ccbReader->readNodeGraphFromFile("./", "TitleScene.ccbi", pScene);
  CCLOG("test");

  if (node != NULL) {
    pScene->addChild(node);
  }

  // run
  pDirector->pushScene(pScene);

  return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
  CCDirector::sharedDirector()->pause();

  // if you use SimpleAudioEngine, it must be pause
  // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
  CCDirector::sharedDirector()->resume();

  // if you use SimpleAudioEngine, it must resume here
  // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
