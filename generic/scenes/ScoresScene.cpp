//
// Created by tsug on 04/07/12.
//

#include "ScoresScene.h"
#include "Assets.h"
#include "AppDelegate.h"
#include "TitleScene.h"
#include "Social.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* ScoresScene::scene() {
  CCScene* scene = CCScene::create();
  scene->addChild(ScoresScene::create());
  return scene;
}

ScoresScene::ScoresScene()
: state(ScoresState::myself)
, myself(nullptr) {
}

bool ScoresScene::init() {
  if (!CCLayer::init()) {
    return false;
  }

  scores = Social::getMyScores();

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

  CCLabelBMFont* _index = CCLabelBMFont::create("#", "coopblack32.fnt");
  _index->setPositionX(64);
  _index->setPositionY(Assets::designResolutionSize.height - 128);
  _index->setAnchorPoint(CCPointZero);
  addChild(_index);

  CCLabelBMFont* _score = CCLabelBMFont::create("score", "coopblack32.fnt");
  _score ->setPositionX(64 + 48);
  _score ->setPositionY(Assets::designResolutionSize.height - 128);
  _score->setAnchorPoint(CCPointZero);
  addChild(_score);

  CCLabelBMFont* _name = CCLabelBMFont::create("name", "coopblack32.fnt");
  _name->setPositionX(64 + (Assets::designResolutionSize.width - 48) / 3);
  _name->setPositionY(Assets::designResolutionSize.height - 128);
  _name->setAnchorPoint(CCPointZero);
  addChild(_name);

  CCLabelBMFont* _level = CCLabelBMFont::create("l.", "coopblack32.fnt");
  _level->setPositionX(64 + ((Assets::designResolutionSize.width - 48) * 5 / 9));
  _level->setPositionY(Assets::designResolutionSize.height - 128);
  _level->setAnchorPoint(CCPointZero);
  addChild(_level);

  CCLabelBMFont* _time = CCLabelBMFont::create("time", "coopblack32.fnt");
  _time->setPositionX(64 + ((Assets::designResolutionSize.width - 48) * 2 / 3));
  _time->setPositionY(Assets::designResolutionSize.height - 128);
  _time->setAnchorPoint(CCPointZero);
  addChild(_time);

  tableView = CCTableView::create(this, CCSizeMake(Assets::designResolutionSize.width - 48, Assets::designResolutionSize.height - 238));
  tableView->setDirection(kCCScrollViewDirectionVertical);
  tableView->setPosition(64, 106);
  tableView->setDelegate(this);
  tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
  this->addChild(tableView);
  tableView->reloadData();

  // Start scheduling
  schedule(schedule_selector(ScoresScene::update));

  return true;
}

void ScoresScene::update(float dt) {
  if (myself != nullptr) {
    CCLabelTTF* score = static_cast<CCLabelTTF*>(myself->getChildByTag(2));
    score->setColor(ccc3(static_cast<GLubyte>(random.nextInt() % 256), static_cast<GLubyte>(random.nextInt() % 256), static_cast<GLubyte>(random.nextInt() % 256)));
  }
}

void ScoresScene::yoursAction(CCObject* sender) {
  state = ScoresState::myself;
  scores = Social::getMyScores();
  tableView->reloadData();
}

void ScoresScene::friendsAction(CCObject* sender) {
  state = ScoresState::friends;
  scores = Social::getFriendsScores();
  tableView->reloadData();
}

void ScoresScene::worldAction(CCObject* sender) {
  state = ScoresState::world;
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
  return CCSizeMake(Assets::designResolutionSize.width - 48, 40);
}

CCTableViewCell* ScoresScene::tableCellAtIndex(CCTableView* table, unsigned int idx) {
  CCString* index = nullptr;
  CCString* score = nullptr;
  CCString* name = nullptr;
  CCString* level = nullptr;
  CCString* time = nullptr;

  CCTableViewCell* cell = table->dequeueCell();
  try {
    ScoreEntry entry = scores.at(idx);
    index = CCString::createWithFormat("%d.", idx + 1);
    score = CCString::create(entry.score);
    name = CCString::create(entry.firstName);
    level = CCString::create(entry.level);
    time = CCString::createWithFormat("%02d:%02d:%02d", static_cast<int32_t>(atoi(entry.time.c_str()) / (60 * 1000)), static_cast<int32_t>(atoi(entry.time.c_str()) / 1000) % 60, static_cast<int32_t>(atoi(entry.time.c_str()) / 10) % 100);
    if (state == ScoresState::myself) {
      myself = nullptr;
    } else if ((AppDelegate::getFirstName() == entry.firstName) && (AppDelegate::getLastName() == entry.lastName)) {
      myself = cell;
    }
  } catch (std::logic_error e) {
  }

  if (!cell) {
    cell = new CCTableViewCell();
    cell->autorelease();

    CCLabelTTF* _index = CCLabelTTF::create(index == nullptr ? "" : index->getCString(), "SkaterDudes.ttf", 20);
    _index->setPosition(CCPointZero);
    _index->setAnchorPoint(CCPointZero);
    _index->setTag(1);
    cell->addChild(_index);

    CCLabelTTF* _score = CCLabelTTF::create(score == nullptr ? "" : score->getCString(), "SkaterDudes.ttf", 20);
    _score ->setPositionX(48);
    _score->setAnchorPoint(CCPointZero);
    _score->setTag(2);
    _score->setColor(ccWHITE);
    cell->addChild(_score);

    CCLabelTTF* _name = CCLabelTTF::create(name == nullptr ? "" : name->getCString(), "SkaterDudes.ttf", 20);
    _name->setPositionX((Assets::designResolutionSize.width - 48) / 3);
    _name->setAnchorPoint(CCPointZero);
    _name->setTag(3);
    cell->addChild(_name);

    CCLabelTTF* _level = CCLabelTTF::create(level == nullptr ? "" : level->getCString(), "SkaterDudes.ttf", 20);
    _level->setPositionX((Assets::designResolutionSize.width - 48) * 5 / 9);
    _level->setAnchorPoint(CCPointZero);
    _level->setTag(4);
    cell->addChild(_level);

    CCLabelTTF* _time = CCLabelTTF::create(time == nullptr ? "" : time->getCString(), "SkaterDudes.ttf", 20);
    _time->setPositionX(((Assets::designResolutionSize.width - 48) * 2 / 3) - 16);
    _time->setAnchorPoint(CCPointZero);
    _time->setTag(5);
    cell->addChild(_time);
  } else {
    CCLabelTTF* _index = (CCLabelTTF*) cell->getChildByTag(1);
    _index->setString(index == nullptr ? "" : index->getCString());

    CCLabelTTF* _score = (CCLabelTTF*) cell->getChildByTag(2);
    _score->setString(score == nullptr ? "" : score->getCString());
    _score->setColor(ccWHITE);

    CCLabelTTF* _name = (CCLabelTTF*) cell->getChildByTag(3);
    _name->setString(name == nullptr ? "" : name->getCString());

    CCLabelTTF* _level = (CCLabelTTF*) cell->getChildByTag(4);
    _level->setString(level == nullptr ? "" : level->getCString());

    CCLabelTTF* _time = (CCLabelTTF*) cell->getChildByTag(5);
    _time->setString(time == nullptr ? "" : time->getCString());
  }

  return cell;
}

unsigned int ScoresScene::numberOfCellsInTableView(CCTableView* table) {
  return scores.size() < 18 ? 18 : scores.size();
}
