//
// Created by tsug on 04/07/12.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "TitleScene.h"
#include "SceneConstants.h"
#include "TutorialScene.h"
#include "PanelScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

TitleScene::TitleScene() {
}

CCScene *TitleScene::scene() {
  CCScene *scene = CCScene::create();
  TitleScene *layer = TitleScene::create();
  scene->addChild(layer);
  return scene;
}

bool TitleScene::init() {
  if (!CCLayer::init()) {
    return false;
  }

  // Start music
  SimpleAudioEngine::sharedEngine()->playBackgroundMusic("harmonic.mp3", true);

  // Background
  cocos2d::CCSprite *bg = cocos2d::CCSprite::create("title.png");
  bg->setAnchorPoint(ccp(0, 0));
  bg->setPosition(ccp(0, 18));
  addChild(bg);

    /** Creates and return a button with a default background and title color. */
  CCScale9Sprite *skipBackgroundButton = CCScale9Sprite::create("button.png");
  CCScale9Sprite *skipBackgroundHighlightedButton = CCScale9Sprite::create("buttonHighlighted.png");
  endlessButton = CCControlButton::create(CCLabelTTF::create("Endless Game", "SkaterDudes.ttf", 32), skipBackgroundButton);
  endlessButton->setBackgroundSpriteForState(skipBackgroundHighlightedButton, CCControlStateHighlighted);
  endlessButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  endlessButton->setPosition(ccp(SceneConstants::designResolutionSize.width / 2, SceneConstants::designResolutionSize.height / 2 + 40));
  endlessButton->setPreferredSize(CCSizeMake(endlessButton->getContentSize().width + 20, 60));
  endlessButton->addTargetWithActionForControlEvents(this, cccontrol_selector(TitleScene::endlessGameAction), CCControlEventTouchUpInside);
  addChild(endlessButton);

  CCScale9Sprite *resumeBackgroundButton = CCScale9Sprite::create("button.png");
  CCScale9Sprite *resumeBackgroundHighlightedButton = CCScale9Sprite::create("buttonHighlighted.png");
  tutorialButton = CCControlButton::create(CCLabelTTF::create("Tutorial", "SkaterDudes.ttf", 32), resumeBackgroundButton);
  tutorialButton->setBackgroundSpriteForState(resumeBackgroundHighlightedButton, CCControlStateHighlighted);
  tutorialButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  tutorialButton->setPosition(ccp(SceneConstants::designResolutionSize.width / 2, SceneConstants::designResolutionSize.height / 2 - 40));
  tutorialButton->setPreferredSize(CCSizeMake(tutorialButton->getContentSize().width + 20, 60));
  tutorialButton->addTargetWithActionForControlEvents(this, cccontrol_selector(TitleScene::tutorialAction), CCControlEventTouchUpInside);
  addChild(tutorialButton);

  CCLabelTTF *copyright = CCLabelTTF::create("Copyright 2012 PixodromE", "SkaterDudes.ttf", 32);
  copyright->setPosition(ccp(SceneConstants::designResolutionSize.width / 2, SceneConstants::designResolutionSize.height / 16 ));
  copyright->setColor(ccc3(10, 10, 10));
  addChild(copyright);

  return true;
}

void TitleScene::endlessGameAction(CCObject *sender) {
  CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::create(2.0f, PanelScene::scene(), kOrientationUpOver));
}

void TitleScene::tutorialAction(CCObject *sender) {
  CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::create(2.0f, TutorialScene::scene(), kOrientationUpOver));
}