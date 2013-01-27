//
// Created by tsug on 04/07/12.
//
//

#include "ScoresScene.h"
#include "Assets.h"
#include "AppDelegate.h"
#include "TitleScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* ScoresScene::scene() {
  CCScene* scene = CCScene::create();
  scene->addChild(ScoresScene::create());
  return scene;
}

bool ScoresScene::init() {
  if (!CCLayer::init()) {
    return false;
  }

  // Background
  CCSprite* bgMiddle = cocos2d::CCSprite::createWithSpriteFrame(AppDelegate::assets.BG_MIDDLE);
  bgMiddle->setAnchorPoint(ccp(0, 0));
  bgMiddle->setPosition(ccp(0, 18));
  addChild(bgMiddle);

  CCSprite* bgBottom = cocos2d::CCSprite::createWithSpriteFrame(AppDelegate::assets.BG_BOTTOM);
  bgBottom->setAnchorPoint(ccp(0, 0));
  bgBottom->setPosition(ccp(0, 0));
  addChild(bgBottom);

  CCSprite* bgTop = cocos2d::CCSprite::createWithSpriteFrame(AppDelegate::assets.BG_TOP);
  bgTop->setAnchorPoint(ccp(0, 0));
  bgTop->setPosition(ccp(0, Assets::designResolutionSize.height - 79));
  addChild(bgTop);

  // Buttons
  CCControlButton* yours = CCControlButton::create(CCLabelTTF::create("Yours", "SkaterDudes.ttf", 24), CCScale9Sprite::create("button.png"));
  yours->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  yours->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  yours->setPosition(ccp(Assets::designResolutionSize.width * 1 / 4, Assets::designResolutionSize.height - 40));
  yours->setPreferredSize(CCSizeMake(yours->getContentSize().width + 10, 60));
//  menuButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ScoresScene::menuAction), CCControlEventTouchUpInside);
  yours->setDefaultTouchPriority(-64);
  addChild(yours);

  CCControlButton* friends = CCControlButton::create(CCLabelTTF::create("Friends", "SkaterDudes.ttf", 24), CCScale9Sprite::create("button.png"));
  friends->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  friends->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  friends->setPosition(ccp(Assets::designResolutionSize.width * 2 / 4, Assets::designResolutionSize.height - 40));
  friends->setPreferredSize(CCSizeMake(friends->getContentSize().width + 10, 60));
//  menuButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ScoresScene::menuAction), CCControlEventTouchUpInside);
  friends->setDefaultTouchPriority(-64);
  addChild(friends);

  CCControlButton* world = CCControlButton::create(CCLabelTTF::create("World", "SkaterDudes.ttf", 24), CCScale9Sprite::create("button.png"));
  world->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  world->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  world->setPosition(ccp(Assets::designResolutionSize.width * 3 / 4, Assets::designResolutionSize.height - 40));
  world->setPreferredSize(CCSizeMake(world->getContentSize().width + 10, 60));
//  menuButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ScoresScene::menuAction), CCControlEventTouchUpInside);
  world->setDefaultTouchPriority(-64);
  addChild(world);

  CCControlButton* endGameButton = CCControlButton::create(CCLabelTTF::create("Back to Title", "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
  endGameButton->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  endGameButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  endGameButton->setPosition(ccp(Assets::designResolutionSize.width / 2, 60));
  endGameButton->setPreferredSize(CCSizeMake(endGameButton->getContentSize().width + 20, 60));
  endGameButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ScoresScene::backToTitleAction), CCControlEventTouchUpInside);
  addChild(endGameButton);

  return true;
}

void ScoresScene::backToTitleAction(CCObject* sender) {
  CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::create(Assets::transitionDuration, TitleScene::scene(), kOrientationUpOver));
}
