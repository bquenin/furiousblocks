//
// Created by tsug on 04/07/12.
//
//

#include "ScoresScene.h"
#include "Assets.h"
#include "AppDelegate.h"
#include "TitleScene.h"
#include "Social.h"

using namespace cocos2d;
using namespace CocosDenshion;

std::vector<ScoreEntry> ScoresScene::scores;

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
  CCSprite* bgMiddle = CCSprite::createWithSpriteFrame(AppDelegate::assets.BG_MIDDLE);
  bgMiddle->setAnchorPoint(ccp(0, 0));
  bgMiddle->setPosition(ccp(0, 18));
  addChild(bgMiddle);

  CCSprite* bgBottom = CCSprite::createWithSpriteFrame(AppDelegate::assets.BG_BOTTOM);
  bgBottom->setAnchorPoint(ccp(0, 0));
  bgBottom->setPosition(ccp(0, 0));
  addChild(bgBottom);

  CCSprite* bgTop = CCSprite::createWithSpriteFrame(AppDelegate::assets.BG_TOP);
  bgTop->setAnchorPoint(ccp(0, 0));
  bgTop->setPosition(ccp(0, Assets::designResolutionSize.height - 79));
  addChild(bgTop);

  // Buttons
  CCControlButton* yours = CCControlButton::create(CCLabelTTF::create("Yours", "SkaterDudes.ttf", 24), CCScale9Sprite::create("button.png"));
  yours->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  yours->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  yours->setPosition(ccp(Assets::designResolutionSize.width * 1 / 4, Assets::designResolutionSize.height - 40));
  yours->setPreferredSize(CCSizeMake(yours->getContentSize().width + 10, 60));
  yours->addTargetWithActionForControlEvents(this, cccontrol_selector(ScoresScene::yoursAction), CCControlEventTouchUpInside);
  yours->setDefaultTouchPriority(-64);
  addChild(yours);

  CCControlButton* friends = CCControlButton::create(CCLabelTTF::create("Friends", "SkaterDudes.ttf", 24), CCScale9Sprite::create("button.png"));
  friends->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  friends->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  friends->setPosition(ccp(Assets::designResolutionSize.width * 2 / 4, Assets::designResolutionSize.height - 40));
  friends->setPreferredSize(CCSizeMake(friends->getContentSize().width + 10, 60));
  friends->addTargetWithActionForControlEvents(this, cccontrol_selector(ScoresScene::friendsAction), CCControlEventTouchUpInside);
  friends->setDefaultTouchPriority(-64);
  addChild(friends);

  CCControlButton* world = CCControlButton::create(CCLabelTTF::create("World", "SkaterDudes.ttf", 24), CCScale9Sprite::create("button.png"));
  world->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  world->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  world->setPosition(ccp(Assets::designResolutionSize.width * 3 / 4, Assets::designResolutionSize.height - 40));
  world->setPreferredSize(CCSizeMake(world->getContentSize().width + 10, 60));
  world->addTargetWithActionForControlEvents(this, cccontrol_selector(ScoresScene::worldAction), CCControlEventTouchUpInside);
  world->setDefaultTouchPriority(-64);
  addChild(world);

  CCControlButton* endGameButton = CCControlButton::create(CCLabelTTF::create("Back to Title", "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
  endGameButton->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  endGameButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  endGameButton->setPosition(ccp(Assets::designResolutionSize.width / 2, 60));
  endGameButton->setPreferredSize(CCSizeMake(endGameButton->getContentSize().width + 20, 60));
  endGameButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ScoresScene::backToTitleAction), CCControlEventTouchUpInside);
  addChild(endGameButton);

  CCSize winSize = CCDirector::sharedDirector()->getWinSize();

  tableView = CCTableView::create(this, CCSizeMake(Assets::designResolutionSize.width - 128, 180));
  tableView->setDirection(kCCScrollViewDirectionVertical);
  tableView->setPosition(64, Assets::designResolutionSize.height /2);
  tableView->setDelegate(this);
  tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
  this->addChild(tableView);
  tableView->reloadData();

  return true;
}

void ScoresScene::yoursAction(CCObject* sender) {
  scores = Social::getMyScores();
  tableView->reloadData();
}

void ScoresScene::friendsAction(CCObject* sender) {
  scores = Social::getFriendsScores();
  tableView->reloadData();
}

void ScoresScene::worldAction(CCObject* sender) {
  scores = Social::getWorldScores();
  tableView->reloadData();
}

void ScoresScene::backToTitleAction(CCObject* sender) {
  CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::create(Assets::transitionDuration, TitleScene::scene(), kOrientationUpOver));
}

void ScoresScene::tableCellTouched(CCTableView* table, CCTableViewCell* cell) {
  CCLOG("cell touched at index: %i", cell->getIdx());
}

CCSize ScoresScene::cellSizeForTable(CCTableView* table) {
  return CCSizeMake(Assets::designResolutionSize.width - 128, 30);
}

CCTableViewCell* ScoresScene::tableCellAtIndex(CCTableView* table, unsigned int idx) {
  ScoreEntry entry = scores.at(idx);
  CCString* index = CCString::createWithFormat("%d. %-12s %-12s %s", idx + 1, entry.score.c_str(), entry.firstName.c_str(), entry.duration.c_str());
  CCTableViewCell* cell = table->dequeueCell();

  if (!cell) {
    cell = new CCTableViewCell();
    cell->autorelease();

    CCLabelTTF* label = CCLabelTTF::create(index->getCString(), "SkaterDudes.ttf", 24);
    label->setPosition(CCPointZero);
    label->setAnchorPoint(CCPointZero);
    label->setTag(123);
    cell->addChild(label);

//    CCLabelTTF* firstName = CCLabelTTF::create(scores.at(idx).firstName.c_str(), "SkaterDudes.ttf", 24);
//    label->setPosition(CCPointZero);
//    label->setAnchorPoint(CCPointZero);
//    cell->addChild(firstName);
  }
  else {
    CCLabelTTF* label = (CCLabelTTF*) cell->getChildByTag(123);
    label->setString(index->getCString());
  }

  return cell;
}

unsigned int ScoresScene::numberOfCellsInTableView(CCTableView* table) {
  return scores.size();
}
