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
  bg = CCSprite::createWithSpriteFrame(AppDelegate::assets.TITLE);
  bg->setAnchorPoint(ccp(0, 0));
  bg->setPosition(ccp(0, 18));
  addChild(bg);

  /** Creates and return a button with a default background and title color. */
  endlessBackgroundButton = CCScale9Sprite::createWithSpriteFrame(AppDelegate::assets.BUTTON);
  endlessBackgroundHighlightedButton = CCScale9Sprite::createWithSpriteFrame(AppDelegate::assets.BUTTONHIGHLIGHTED);
  endlessButtonLabel = CCLabelBMFont::create("Endless Game", "SkaterDudes.fnt");
  endlessButton = CCControlButton::create(endlessButtonLabel, endlessBackgroundButton);
  endlessButton->setBackgroundSpriteForState(endlessBackgroundHighlightedButton, CCControlStateHighlighted);
  endlessButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  endlessButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 + 40));
  endlessButton->setPreferredSize(CCSizeMake(endlessButton->getContentSize().width + 20, 60));
  endlessButton->addTargetWithActionForControlEvents(this, cccontrol_selector(TitleScene::endlessGameAction), CCControlEventTouchUpInside);
  addChild(endlessButton);

  tutorialBackgroundButton = CCScale9Sprite::createWithSpriteFrame(AppDelegate::assets.BUTTON);
  tutorialBackgroundHighlightedButton = CCScale9Sprite::createWithSpriteFrame(AppDelegate::assets.BUTTONHIGHLIGHTED);
  tutorialButtonLabel = CCLabelBMFont::create("Tutorial", "SkaterDudes.fnt");
  tutorialButton = CCControlButton::create(tutorialButtonLabel, tutorialBackgroundButton);
  tutorialButton->setBackgroundSpriteForState(tutorialBackgroundHighlightedButton, CCControlStateHighlighted);
  tutorialButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  tutorialButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 - 40));
  tutorialButton->setPreferredSize(CCSizeMake(tutorialButton->getContentSize().width + 20, 60));
  tutorialButton->addTargetWithActionForControlEvents(this, cccontrol_selector(TitleScene::tutorialAction), CCControlEventTouchUpInside);
  addChild(tutorialButton);

  copyright = CCLabelBMFont::create("Copyright 2012 PixodromE", "SkaterDudes.fnt");
  copyright->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 16 ));
  copyright->setColor(ccc3(10, 10, 10));
  addChild(copyright);

  return true;
}

void TitleScene::endlessGameAction(CCObject *sender) {
  CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::create(Assets::transitionDuration, PanelScene::scene(), kOrientationUpOver));
}

void TitleScene::tutorialAction(CCObject *sender) {
  CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::create(Assets::transitionDuration, TutorialScene::scene(), kOrientationUpOver));
}