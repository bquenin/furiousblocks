//
// Created by bquenin on 11/2/12.
//
// To change the template use AppCode | Preferences | File Templates.
//

#include "AbstractPanelScene.h"
#include "Assets.h"
#include "AppDelegate.h"

AbstractPanelScene::AbstractPanelScene()
: tick(1)
, stateTime(0)
, gameRunning(false) {
}

AbstractPanelScene::~AbstractPanelScene() {
  delete core;
}

bool AbstractPanelScene::init() {
  batch = CCSpriteBatchNode::create("blocks.png", 100);
  addChild(batch);

  // Background
  cocos2d::CCSprite *bgMiddle = cocos2d::CCSprite::createWithSpriteFrame(AppDelegate::assets.BG_MIDDLE);
  bgMiddle->setAnchorPoint(ccp(0, 0));
  bgMiddle->setPosition(ccp(0, 18));
  batch->addChild(bgMiddle);

  // Initialize the grid
  for (int y = 0; y < FuriousBlocksCoreDefaults::PANEL_HEIGHT + 1; y++) {
    for (int x = 0; x < FuriousBlocksCoreDefaults::PANEL_WIDTH; x++) {
      grid[x][y] = cocos2d::CCSprite::createWithSpriteFrame(AppDelegate::assets.GARBAGE_PLAIN);
      grid[x][y]->setAnchorPoint(ccp(0, 0));
      grid[x][y]->setVisible(false);
      grid[x][y]->setPosition(ccp(xOffset + x * Assets::TILE_SIZE, yOffset + y * Assets::TILE_SIZE));
      batch->addChild(grid[x][y]);
    }
  }

  cocos2d::CCSprite *bgBottom = cocos2d::CCSprite::createWithSpriteFrame(AppDelegate::assets.BG_BOTTOM);
  bgBottom->setAnchorPoint(ccp(0, 0));
  bgBottom->setPosition(ccp(0, 0));
  batch->addChild(bgBottom);

  cocos2d::CCSprite *bgTop = cocos2d::CCSprite::createWithSpriteFrame(AppDelegate::assets.BG_TOP);
  bgTop->setAnchorPoint(ccp(0, 0));
  bgTop->setPosition(ccp(0, Assets::designResolutionSize.height - 79));
  batch->addChild(bgTop);

  return true;
}
