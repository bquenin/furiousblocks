//
// Created by tsug on 04/07/12.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "TitleScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
// using namespace CocosDenshion;

TitleScene::TitleScene()
//: mBurstSprite(NULL)
//, mTestTitleLabelTTF(NULL)
{
}

TitleScene::~TitleScene() {
  //  CC_SAFE_RELEASE(mBurstSprite);
  //  CC_SAFE_RELEASE(mTestTitleLabelTTF);
}

//void TitleScene::openTest(const char * pCCBFileName, const char * pCCNodeName, CCNodeLoader * pCCNodeLoader) {
//  /* Create an autorelease CCNodeLoaderLibrary. */
//  CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
//
//  ccNodeLoaderLibrary->registerCCNodeLoader("TestHeaderLayer", TestHeaderLayerLoader::loader());
//  if(pCCNodeName != NULL && pCCNodeLoader != NULL) {
//    ccNodeLoaderLibrary->registerCCNodeLoader(pCCNodeName, pCCNodeLoader);
//  }
//
//  /* Create an autorelease CCBReader. */
//  cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
//  ccbReader->autorelease();
//
//  /* Read a ccbi file. */
//  // Load the scene from the ccbi-file, setting this class as
//  // the owner will cause lblTestTitle to be set by the CCBReader.
//  // lblTestTitle is in the TestHeader.ccbi, which is referenced
//  // from each of the test scenes.
//  CCNode * node = ccbReader->readNodeGraphFromFile("ccb/official/pub/", pCCBFileName, this);
//
//  this->mTestTitleLabelTTF->setString(pCCBFileName);
//
//  CCScene * scene = CCScene::create();
//  if(node != NULL) {
//    scene->addChild(node);
//  }
//
//  /* Push the new scene with a fancy transition. */
//  ccColor3B transitionColor;
//  transitionColor.r = 0;
//  transitionColor.g = 0;
//  transitionColor.b = 0;
//
//  CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene, transitionColor));
//}


void TitleScene::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader) {
  //  CCRotateBy * ccRotateBy = CCRotateBy::create(0.5f, 10);
  //  CCRepeatForever * ccRepeatForever = CCRepeatForever::create(ccRotateBy);
  //  this->mBurstSprite->runAction(ccRepeatForever);
  //  SimpleAudioEngine::sharedEngine()->playBackgroundMusic(std::string(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("harmonic.mp3")).c_str(), true);
  //  CCLOG("Playing bg music");
}


SEL_MenuHandler TitleScene::onResolveCCBCCMenuItemSelector(CCObject *pTarget, CCString *pSelectorName) {
  return NULL;
}

SEL_CCControlHandler TitleScene::onResolveCCBCCControlSelector(CCObject *pTarget, CCString *pSelectorName) {
  CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onArcade", TitleScene::onArcadeClicked);

  return NULL;
}

bool TitleScene::onAssignCCBMemberVariable(CCObject *pTarget, CCString *pMemberVariableName, CCNode *pNode) {
  //  CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBurstSprite", CCSprite *, this->mBurstSprite);
  //  CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTestTitleLabelTTF", CCLabelTTF *, this->mTestTitleLabelTTF);

  return false;
}


void TitleScene::onArcadeClicked(CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
  //this->openTest("ccb/MenuTest.ccbi", "MenuTestLayer", MenuTestLayerLoader::loader());
  CCLOG("Arcade clicked!");
  //  void *ptr = malloc(1048576);
}

