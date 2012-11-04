//
// Created by bquenin on 11/2/12.
//
// To change the template use AppCode | Preferences | File Templates.
//

#include <boost/bind.hpp>
#include "AbstractPanelScene.h"
#include "GarbageBlockType.h"

AbstractPanelScene::AbstractPanelScene()
: tick(1)
, stateTime(0)
, gameRunning(false) {
}

bool AbstractPanelScene::init() {
  setTouchEnabled(true);

  // Sprite sheet
  cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("blocks.plist");
  batch = cocos2d::CCSpriteBatchNode::create("blocks.png", 100);
  addChild(batch);

  // Frame assets
  BLOCKS_RED_PANIC_01 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-panic-01.png");
  BLOCKS_BLUE_HOVER_01 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-hover-01.png");
  BLOCKS_GREEN_COMPRESSED_01 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-compressed-01.png");
  BLOCKS_BLUE_FLASH = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-flash.png");
  GARBAGE_BLINK = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-single-flash.png");
  BLOCKS_PURPLE_PANIC_01 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-panic-01.png");
  BLOCKS_RED_LAND_02 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-land-02.png");
  BLOCKS_YELLOW_HAPPY = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-happy.png");
  BLOCKS_RED_PANIC_03 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-panic-03.png");
  BLOCKS_BLUE_HAPPY = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-happy.png");
  BLOCKS_BLUE_PANIC_01 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-panic-01.png");
  CURSOR_01 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("cursor-01.png");
  GARBAGE_TOP = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-top.png");
  CURSOR_03 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("cursor-03.png");
  BLOCKS_YELLOW_HOVER_03 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-hover-03.png");
  BLOCKS_PURPLE_HOVER_01 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-hover-01.png");
  BLOCKS_YELLOW_HOVER_02 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-hover-02.png");
  BLOCKS_GREEN_IDLE = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-idle.png");
  //        DRAW = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("EndPopUp-Draw.png");
  BLOCKS_BLUE_PANIC_02 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-panic-02.png");
  //        WIN = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("EndPopUp-Win.png");
  BLOCKS_GREEN_FLASH = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-flash.png");
  BLOCKS_RED_HOVER_04 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-hover-04.png");
  BLOCKS_RED_PANIC_04 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-panic-04.png");
  GARBAGE_RIGHT_BOTTOM = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-right-bottom.png");
  GARBAGE_TOP_RIGHT_BOTTOM = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-top-right-bottom.png");
  BLOCKS_BLUE_PANIC_04 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-panic-04.png");
  //        EYE_SURPRISE = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("eye-surprise.png");
  BLOCKS_GREEN_LAND_02 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-land-02.png");
  GARBAGE_TOP_BOTTOM = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-top-bottom.png");
  BLOCKS_GREEN_COMPRESSED_02 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-compressed-02.png");
  BLOCKS_PURPLE_PANIC_04 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-panic-04.png");
  GARBAGE_LEFT = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-left.png");
  CURSOR_02 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("cursor-02.png");
  BLOCKS_PURPLE_HOVER_03 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-hover-03.png");
  BLOCKS_YELLOW_COMPRESSED_03 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-compressed-03.png");
  BLOCKS_YELLOW_PANIC_04 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-panic-04.png");
  GARBAGE_PLAIN = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-plain.png");
  BLOCKS_RED_HOVER_01 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-hover-01.png");
  BLOCKS_BLUE_COMPRESSED_04 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-compressed-04.png");
  BLOCKS_PURPLE_IDLE = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-idle.png");
  BLOCKS_PURPLE_HOVER_04 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-hover-04.png");
  BLOCKS_PURPLE_PANIC_02 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-panic-02.png");
  BLOCKS_GREEN_COMPRESSED_03 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-compressed-03.png");
  BLOCKS_RED_IDLE = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-idle.png");
  BLOCKS_YELLOW_HOVER_01 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-hover-01.png");
  BLOCKS_PURPLE_LAND_01 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-land-01.png");
  BLOCKS_PURPLE_COMPRESSED_04 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-compressed-04.png");
  BLOCKS_YELLOW_COMPRESSED_01 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-compressed-01.png");
  BLOCKS_PURPLE_COMPRESSED_02 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-compressed-02.png");
  BLOCKS_RED_COMPRESSED_01 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-compressed-01.png");
  BLOCKS_RED_HOVER_02 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-hover-02.png");
  GARBAGE_TOP_LEFT = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-top-left.png");
  BLOCKS_PURPLE_COMPRESSED_03 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-compressed-03.png");
  BLOCKS_RED_COMPRESSED_04 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-compressed-04.png");
  GARBAGE_TOP_LEFT_BOTTOM = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-top-left-bottom.png");
  BLOCKS_YELLOW_IDLE = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-idle.png");
  BLOCKS_PURPLE_LAND_02 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-land-02.png");
  BLOCKS_PURPLE_HAPPY = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-happy.png");
  BLOCKS_BLUE_COMPRESSED_03 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-compressed-03.png");
  BLOCKS_BLUE_HOVER_03 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-hover-03.png");
  GARBAGE_RIGHT = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-right.png");
  BLOCKS_RED_PANIC_02 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-panic-02.png");
  BLOCKS_GREEN_HAPPY = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-happy.png");
  BLOCKS_GREEN_PANIC_02 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-panic-02.png");
  BLOCKS_YELLOW_LAND_02 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-land-02.png");
  BLOCKS_BLUE_HOVER_02 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-hover-02.png");
  BLOCKS_RED_HOVER_03 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-hover-03.png");
  BLOCKS_GREEN_LAND_01 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-land-01.png");
  BLOCKS_BLUE_IDLE = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-idle.png");
  BLOCKS_RED_HAPPY = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-happy.png");
  BLOCKS_YELLOW_HOVER_04 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-hover-04.png");
  GARBAGE_SINGLE = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-single.png");
  //        EYE = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("eye.png");
  BLOCKS_GREEN_PANIC_03 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-panic-03.png");
  GARBAGE_LEFT_BOTTOM = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-left-bottom.png");
  BLOCKS_BLUE_PANIC_03 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-panic-03.png");
  //        LOSE = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("EndPopUp-Lose.png");
  BLOCKS_GREEN_HOVER_02 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-hover-02.png");
  BLOCKS_YELLOW_PANIC_03 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-panic-03.png");
  BLOCKS_PURPLE_FLASH = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-flash.png");
  BLOCKS_BLUE_COMPRESSED_01 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-compressed-01.png");
  BLOCKS_GREEN_COMPRESSED_04 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-compressed-04.png");
  BLOCKS_RED_LAND_01 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-land-01.png");
  BLOCKS_YELLOW_COMPRESSED_04 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-compressed-04.png");
  BLOCKS_RED_COMPRESSED_03 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-compressed-03.png");
  GARBAGE_BOTTOM = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-bottom.png");
  BLOCKS_GREEN_PANIC_04 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-panic-04.png");
  BLOCKS_RED_COMPRESSED_02 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-compressed-02.png");
  BLOCKS_BLUE_HOVER_04 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-hover-04.png");
  BLOCKS_YELLOW_PANIC_01 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-panic-01.png");
  BLOCKS_GREEN_HOVER_04 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-hover-04.png");
  BLOCKS_GREEN_HOVER_01 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-hover-01.png");
  BLOCKS_BLUE_LAND_02 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-land-02.png");
  BLOCKS_YELLOW_FLASH = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-flash.png");
  BLOCKS_YELLOW_LAND_01 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-land-01.png");
  BLOCKS_PURPLE_COMPRESSED_01 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-compressed-01.png");
  GARBAGE_TOP_RIGHT = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-top-right.png");
  BLOCKS_GREEN_HOVER_03 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-hover-03.png");
  BLOCKS_GREEN_PANIC_01 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-panic-01.png");
  BLOCKS_YELLOW_COMPRESSED_02 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-compressed-02.png");
  BLOCKS_YELLOW_PANIC_02 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-panic-02.png");
  BLOCKS_RED_FLASH = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-flash.png");
  BLOCKS_PURPLE_PANIC_03 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-panic-03.png");
  BLOCKS_PURPLE_HOVER_02 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-hover-02.png");
  BLOCKS_BLUE_COMPRESSED_02 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-compressed-02.png");
  BLOCKS_BLUE_LAND_01 = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-land-01.png");

  YELLOW_PANICKING = new Animation(4, {BLOCKS_YELLOW_PANIC_01, BLOCKS_YELLOW_PANIC_02, BLOCKS_YELLOW_PANIC_03, BLOCKS_YELLOW_PANIC_04, BLOCKS_YELLOW_PANIC_03, BLOCKS_YELLOW_PANIC_02, BLOCKS_YELLOW_PANIC_01});
  BLUE_PANICKING = new Animation(4, {BLOCKS_BLUE_PANIC_01, BLOCKS_BLUE_PANIC_02, BLOCKS_BLUE_PANIC_03, BLOCKS_BLUE_PANIC_04, BLOCKS_BLUE_PANIC_03, BLOCKS_BLUE_PANIC_02, BLOCKS_BLUE_PANIC_01});
  RED_PANICKING = new Animation(4, {BLOCKS_RED_PANIC_01, BLOCKS_RED_PANIC_02, BLOCKS_RED_PANIC_03, BLOCKS_RED_PANIC_04, BLOCKS_RED_PANIC_03, BLOCKS_RED_PANIC_02, BLOCKS_RED_PANIC_01});
  GREEN_PANICKING = new Animation(4, {BLOCKS_GREEN_PANIC_01, BLOCKS_GREEN_PANIC_02, BLOCKS_GREEN_PANIC_03, BLOCKS_GREEN_PANIC_04, BLOCKS_GREEN_PANIC_03, BLOCKS_GREEN_PANIC_02, BLOCKS_GREEN_PANIC_01});
  PURPLE_PANICKING = new Animation(4, {BLOCKS_PURPLE_PANIC_01, BLOCKS_PURPLE_PANIC_02, BLOCKS_PURPLE_PANIC_03, BLOCKS_PURPLE_PANIC_04, BLOCKS_PURPLE_PANIC_03, BLOCKS_PURPLE_PANIC_02, BLOCKS_PURPLE_PANIC_01});

  YELLOW_COMPRESSING = new Animation(4, {BLOCKS_YELLOW_COMPRESSED_01, BLOCKS_YELLOW_COMPRESSED_02, BLOCKS_YELLOW_COMPRESSED_03, BLOCKS_YELLOW_COMPRESSED_04});
  BLUE_COMPRESSING = new Animation(4, {BLOCKS_BLUE_COMPRESSED_01, BLOCKS_BLUE_COMPRESSED_02, BLOCKS_BLUE_COMPRESSED_03, BLOCKS_BLUE_COMPRESSED_04});
  RED_COMPRESSING = new Animation(4, {BLOCKS_RED_COMPRESSED_01, BLOCKS_RED_COMPRESSED_02, BLOCKS_RED_COMPRESSED_03, BLOCKS_RED_COMPRESSED_04});
  GREEN_COMPRESSING = new Animation(4, {BLOCKS_GREEN_COMPRESSED_01, BLOCKS_GREEN_COMPRESSED_02, BLOCKS_GREEN_COMPRESSED_03, BLOCKS_GREEN_COMPRESSED_04});
  PURPLE_COMPRESSING = new Animation(4, {BLOCKS_PURPLE_COMPRESSED_01, BLOCKS_PURPLE_COMPRESSED_02, BLOCKS_PURPLE_COMPRESSED_03, BLOCKS_PURPLE_COMPRESSED_04});

  YELLOW_BLINKING = new Animation(1, {BLOCKS_YELLOW_FLASH, BLOCKS_YELLOW_IDLE});
  BLUE_BLINKING = new Animation(1, {BLOCKS_BLUE_FLASH, BLOCKS_BLUE_IDLE});
  RED_BLINKING = new Animation(1, {BLOCKS_RED_FLASH, BLOCKS_RED_IDLE});
  GREEN_BLINKING = new Animation(1, {BLOCKS_GREEN_FLASH, BLOCKS_GREEN_IDLE});
  PURPLE_BLINKING = new Animation(1, {BLOCKS_PURPLE_FLASH, BLOCKS_PURPLE_IDLE});
  GARBAGE_BLINKING = new Animation(1, {GARBAGE_BLINK, GARBAGE_PLAIN});

  CURSOR = new Animation(16, {CURSOR_01, CURSOR_02, CURSOR_03, CURSOR_02});

  // Background
  cocos2d::CCSprite *bgMiddle = cocos2d::CCSprite::createWithSpriteFrameName("bg-middle.png");
  bgMiddle->setAnchorPoint(ccp(0, 0));
  bgMiddle->setPosition(ccp(0, 8));
  batch->addChild(bgMiddle);

  // Initialize the grid
  for (int y = 0; y < FuriousBlocksCoreDefaults::PANEL_HEIGHT + 1; y++) {
    for (int x = 0; x < FuriousBlocksCoreDefaults::PANEL_WIDTH; x++) {
      grid[x][y] = cocos2d::CCSprite::createWithSpriteFrame(GARBAGE_PLAIN);
      grid[x][y]->setAnchorPoint(ccp(0, 0));
      grid[x][y]->setVisible(false);
      grid[x][y]->setPosition(ccp(xOffset + x * TILE_SIZE, yOffset + y * TILE_SIZE));
      batch->addChild(grid[x][y]);
    }
  }

  cocos2d::CCSprite *bgBottom = cocos2d::CCSprite::createWithSpriteFrameName("bg-bottom.png");
  bgBottom->setAnchorPoint(ccp(0, 0));
  bgBottom->setPosition(ccp(0, 0));
  batch->addChild(bgBottom);

  cocos2d::CCSprite *bgTop = cocos2d::CCSprite::createWithSpriteFrameName("bg-top.png");
  bgTop->setAnchorPoint(ccp(0, 0));
  bgTop->setPosition(ccp(0, 440));
  batch->addChild(bgTop);

  cocos2d::CCSize size = cocos2d::CCDirector::sharedDirector()->getWinSize();

  youLose = cocos2d::CCSprite::createWithSpriteFrameName("lose.png");
  youLose->setPosition(ccp(size.width / 2, size.height / 2));
  youLose->setVisible(false);
  batch->addChild(youLose);

  cocos2d::CCLabelBMFont *scoreLabel = cocos2d::CCLabelBMFont::create("Score", "coopblack32.fnt");
  scoreLabel->setPosition(ccp(size.width / 4, 470));
  addChild(scoreLabel);

  score = cocos2d::CCLabelBMFont::create("Score", "coopblack32.fnt");
  score->setPosition(ccp(size.width / 4, 454));
  addChild(score);

  cocos2d::CCLabelBMFont *timeLabel = cocos2d::CCLabelBMFont::create("Time", "coopblack32.fnt");
  timeLabel->setPosition(ccp(size.width * 3 / 4, 470));
  addChild(timeLabel);

  minutes = cocos2d::CCLabelBMFont::create("Time", "coopblack32.fnt");
  minutes->setPosition(ccp(-32 + size.width * 3 / 4, 454));
  addChild(minutes);

  cocos2d::CCLabelBMFont *colon1 = cocos2d::CCLabelBMFont::create(":", "coopblack32.fnt");
  colon1->setPosition(ccp(-16 + size.width * 3 / 4, 454));
  addChild(colon1);

  seconds = cocos2d::CCLabelBMFont::create("Time", "coopblack32.fnt");
  seconds->setPosition(ccp(size.width * 3 / 4, 454));
  addChild(seconds);

  cocos2d::CCLabelBMFont *colon2 = cocos2d::CCLabelBMFont::create(":", "coopblack32.fnt");
  colon2->setPosition(ccp(16 + size.width * 3 / 4, 454));
  addChild(colon2);

  centisecs = cocos2d::CCLabelBMFont::create("Time", "coopblack32.fnt");
  centisecs->setPosition(ccp(32 + size.width * 3 / 4, 454));
  addChild(centisecs);

  return true;
}

cocos2d::CCSpriteFrame *AbstractPanelScene::getBlockFrame(Block *blockSituation, int64_t tick, bool compressed, bool panicking) {
  NonLoopingAnimation *currentAnimation = animations[blockSituation->id];
  BlockState state = blockSituation->state;
  BlockType type = blockSituation->type;

  switch (state) {
    case BlockState::EXPLODING:
      switch (type) {
        case BlockType::YELLOW:
          return BLOCKS_YELLOW_HAPPY;
        case BlockType::GREEN:
          return BLOCKS_GREEN_HAPPY;
        case BlockType::RED:
          return BLOCKS_RED_HAPPY;
        case BlockType::PURPLE:
          return BLOCKS_PURPLE_HAPPY;
        case BlockType::BLUE:
          return BLOCKS_BLUE_HAPPY;
        case BlockType::GARBAGE:
        case BlockType::INVISIBLE:
        case BlockType::TUTORIAL:
          return nullptr;
      }

    case BlockState::REVEALING:
      return GARBAGE_BLINK;

    case BlockState::AIRBOUNCING:
      if (currentAnimation == nullptr) {
        NonLoopingAnimation *animation = nullptr;
        switch (type) {
          case BlockType::YELLOW:
            animation = new NonLoopingAnimation(tick, 4, {BLOCKS_YELLOW_HOVER_01, BLOCKS_YELLOW_HOVER_02, BLOCKS_YELLOW_HOVER_03, BLOCKS_YELLOW_HOVER_04, BLOCKS_YELLOW_HOVER_03, BLOCKS_YELLOW_HOVER_02, BLOCKS_YELLOW_HOVER_01});
            break;
          case BlockType:: BLUE:
            animation = new NonLoopingAnimation(tick, 4, {BLOCKS_BLUE_HOVER_01, BLOCKS_BLUE_HOVER_02, BLOCKS_BLUE_HOVER_03, BLOCKS_BLUE_HOVER_04, BLOCKS_BLUE_HOVER_03, BLOCKS_BLUE_HOVER_02, BLOCKS_BLUE_HOVER_01});
            break;
          case BlockType:: PURPLE:
            animation = new NonLoopingAnimation(tick, 4, {BLOCKS_PURPLE_HOVER_01, BLOCKS_PURPLE_HOVER_02, BLOCKS_PURPLE_HOVER_03, BLOCKS_PURPLE_HOVER_04, BLOCKS_PURPLE_HOVER_03, BLOCKS_PURPLE_HOVER_02, BLOCKS_PURPLE_HOVER_01});
            break;
          case BlockType:: RED:
            animation = new NonLoopingAnimation(tick, 4, {BLOCKS_RED_HOVER_01, BLOCKS_RED_HOVER_02, BLOCKS_RED_HOVER_03, BLOCKS_RED_HOVER_04, BLOCKS_RED_HOVER_03, BLOCKS_RED_HOVER_02, BLOCKS_RED_HOVER_01});
            break;
          case BlockType:: GREEN:
            animation = new NonLoopingAnimation(tick, 4, {BLOCKS_GREEN_HOVER_01, BLOCKS_GREEN_HOVER_02, BLOCKS_GREEN_HOVER_03, BLOCKS_GREEN_HOVER_04, BLOCKS_GREEN_HOVER_03, BLOCKS_GREEN_HOVER_02, BLOCKS_GREEN_HOVER_01});
            break;
        }
        animations[blockSituation->id] = animation;
        return animation->getKeyFrame(tick);
      }
      //$FALL-THROUGH$

    case BlockState::BLINKING:
    case BlockState::FALLING:
    case BlockState::SWITCHING_BACK:
    case BlockState::SWITCHING_FORTH:
    case BlockState::DONE_BLINKING:
    case BlockState::DONE_REVEALING:
    case BlockState::DONE_HOVERING:
    case BlockState::DONE_SWITCHING_FORTH:
    case BlockState::HOVERING:
    case BlockState::DONE_AIRBOUNCING:
    case BlockState::IDLE:
      if (blockSituation->justLand && state == BlockState::IDLE && type != BlockType::GARBAGE && type != BlockType::TUTORIAL) {
        NonLoopingAnimation *animation = nullptr;
        switch (type) {
          case BlockType:: YELLOW:
            animation = new NonLoopingAnimation(tick, 4, {BLOCKS_YELLOW_LAND_01, BLOCKS_YELLOW_IDLE, BLOCKS_YELLOW_LAND_02, BLOCKS_YELLOW_IDLE});
            break;
          case BlockType:: BLUE:
            animation = new NonLoopingAnimation(tick, 4, {BLOCKS_BLUE_LAND_01, BLOCKS_BLUE_IDLE, BLOCKS_BLUE_LAND_02, BLOCKS_BLUE_IDLE});
            break;
          case BlockType:: PURPLE:
            animation = new NonLoopingAnimation(tick, 4, {BLOCKS_PURPLE_LAND_01, BLOCKS_PURPLE_IDLE, BLOCKS_PURPLE_LAND_02, BLOCKS_PURPLE_IDLE});
            break;
          case BlockType:: RED:
            animation = new NonLoopingAnimation(tick, 4, {BLOCKS_RED_LAND_01, BLOCKS_RED_IDLE, BLOCKS_RED_LAND_02, BLOCKS_RED_IDLE});
            break;
          case BlockType:: GREEN:
            animation = new NonLoopingAnimation(tick, 4, {BLOCKS_GREEN_LAND_01, BLOCKS_GREEN_IDLE, BLOCKS_GREEN_LAND_02, BLOCKS_GREEN_IDLE});
            break;
        }
        delete animations[blockSituation->id];
        animations[blockSituation->id] = animation;
        return animation->getKeyFrame(tick);
      }
      if (currentAnimation != nullptr) {
        if (currentAnimation->isAnimationFinished(tick)) {
          delete animations[blockSituation->id];
          animations.erase(blockSituation->id);
        } else {
          return currentAnimation->getKeyFrame(tick);
        }
      }
      switch (type) {
        case BlockType::YELLOW:
          if (compressed && state == BlockState:: IDLE) {
            return YELLOW_COMPRESSING->getKeyFrame(tick, true);
          }
          if (panicking && state == BlockState:: IDLE) {
            return YELLOW_PANICKING->getKeyFrame(tick, true);
          }
          return state == BlockState:: BLINKING ? YELLOW_BLINKING->getKeyFrame(tick, true) : BLOCKS_YELLOW_IDLE;

        case BlockType:: GREEN:
          if (compressed && state == BlockState:: IDLE) {
            return GREEN_COMPRESSING->getKeyFrame(tick, true);
          }
          if (panicking && state == BlockState:: IDLE) {
            return GREEN_PANICKING->getKeyFrame(tick, true);
          }
          return state == BlockState::BLINKING ? GREEN_BLINKING->getKeyFrame(tick, true) : BLOCKS_GREEN_IDLE;
        case BlockType:: RED:
          if (compressed && state == BlockState:: IDLE) {
            return RED_COMPRESSING->getKeyFrame(tick, true);
          }
          if (panicking && state == BlockState::IDLE) {
            return RED_PANICKING->getKeyFrame(tick, true);
          }
          return state == BlockState::BLINKING ? RED_BLINKING->getKeyFrame(tick, true) : BLOCKS_RED_IDLE;
        case BlockType:: PURPLE:
          if (compressed && state == BlockState::IDLE) {
            return PURPLE_COMPRESSING->getKeyFrame(tick, true);
          }
          if (panicking && state == BlockState::IDLE) {
            return PURPLE_PANICKING->getKeyFrame(tick, true);
          }
          return state == BlockState::BLINKING ? PURPLE_BLINKING->getKeyFrame(tick, true) : BLOCKS_PURPLE_IDLE;
        case BlockType:: BLUE:
          if (compressed && state == BlockState::IDLE) {
            return BLUE_COMPRESSING->getKeyFrame(tick, true);
          }
          if (panicking && state == BlockState::IDLE) {
            return BLUE_PANICKING->getKeyFrame(tick, true);
          }
          return state == BlockState::BLINKING ? BLUE_BLINKING->getKeyFrame(tick, true) : BLOCKS_BLUE_IDLE;
        case BlockType::TUTORIAL:
          return GARBAGE_SINGLE;
        case BlockType::GARBAGE:
          if (state == BlockState:: BLINKING && GARBAGE_BLINKING->getKeyFrame(tick, true) == GARBAGE_BLINK) {
            return GARBAGE_BLINK;
          }

          switch (blockSituation->garbageBlockType) {
            case GarbageBlockType::DOWN:
              return GARBAGE_BOTTOM;
            case GarbageBlockType::DOWNLEFT:
              return GARBAGE_LEFT_BOTTOM;
            case GarbageBlockType::DOWNRIGHT:
              return GARBAGE_RIGHT_BOTTOM;
            case GarbageBlockType::LEFT:
              return GARBAGE_LEFT;
            case GarbageBlockType::PLAIN:
              return GARBAGE_PLAIN;
            case GarbageBlockType::RIGHT:
              return GARBAGE_RIGHT;
            case GarbageBlockType::UP:
              return GARBAGE_TOP;
            case GarbageBlockType::UPDOWN:
              return GARBAGE_TOP_BOTTOM;
            case GarbageBlockType::UPLEFT:
              return GARBAGE_TOP_LEFT;
            case GarbageBlockType::UPLEFTDOWN:
              return GARBAGE_TOP_LEFT_BOTTOM;
            case GarbageBlockType::UPRIGHT:
              return GARBAGE_TOP_RIGHT;
            case GarbageBlockType::UPRIGHTDOWN:
              return GARBAGE_TOP_RIGHT_BOTTOM;
            default:
              break;
          }
        case BlockType ::INVISIBLE:
          return nullptr;
      }

    case BlockState::DONE_EXPLODING:
    case BlockState::TO_DELETE:
      delete animations[blockSituation->id];
      animations.erase(blockSituation->id);
      return nullptr;
  }

  return nullptr;
}

std::string AbstractPanelScene::format(const char *fmt, ...) {
  size_t size = 512;
  char *buffer = 0;
  buffer = new char [size];
  va_list vl;
  va_start(vl, fmt);
  int nsize = vsnprintf(buffer, size, fmt, vl);
  if (size <= nsize) { //fail delete buffer and try again
    delete buffer;
    buffer = new char [nsize + 1];//+1 for /0
    vsnprintf(buffer, size, fmt, vl);
  }
  std::string ret(buffer);
  va_end(vl);
  delete buffer;
  return ret;
}
