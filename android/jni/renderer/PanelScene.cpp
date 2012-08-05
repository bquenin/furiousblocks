#include "PanelScene.h"
#include <thread>

USING_NS_CC;

CCScene *PanelScene::scene() {
  // 'scene' is an autorelease object
  CCScene *scene = CCScene::create();

  // 'layer' is an autorelease object
  PanelScene *layer = PanelScene::create();

  // add layer as a child to scene
  scene->addChild(layer);

  // return the scene
  return scene;
}

void call_from_thread() {
  std::cout << "Hello, World" << std::endl;
}

// on "init" you need to initialize your instance
bool PanelScene::init() {
  if (!CCLayer::init()) {
    return false;
  }

  // Game initialization
  core = new FuriousBlocksCore(0);

  // Player initialization
  player = new Player();
  core->addPlayer(player);

  // Sprite sheet
  CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("blocks.plist");
  CCSpriteBatchNode *batch = CCSpriteBatchNode::create("blocks.png", 100);
  addChild(batch);

  // Frame assets
  BLOCKS_RED_PANIC_01 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-panic-01.png");
  BLOCKS_BLUE_HOVER_01 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-hover-01.png");
  BLOCKS_GREEN_COMPRESSED_01 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-compressed-01.png");
  BLOCKS_BLUE_FLASH = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-flash.png");
  GARBAGE_BLINK = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-single-flash.png");
  BLOCKS_PURPLE_PANIC_01 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-panic-01.png");
  BLOCKS_RED_LAND_02 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-land-02.png");
  BLOCKS_YELLOW_HAPPY = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-happy.png");
  BLOCKS_RED_PANIC_03 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-panic-03.png");
  BLOCKS_BLUE_HAPPY = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-happy.png");
  BLOCKS_BLUE_PANIC_01 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-panic-01.png");
  CURSOR_01 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("cursor-01.png");
  GARBAGE_TOP = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-top.png");
  CURSOR_03 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("cursor-03.png");
  BLOCKS_YELLOW_HOVER_03 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-hover-03.png");
  BLOCKS_PURPLE_HOVER_01 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-hover-01.png");
  BLOCKS_YELLOW_HOVER_02 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-hover-02.png");
  BLOCKS_GREEN_IDLE = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-idle.png");
  //        DRAW = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("EndPopUp-Draw.png");
  BLOCKS_BLUE_PANIC_02 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-panic-02.png");
  //        WIN = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("EndPopUp-Win.png");
  BLOCKS_GREEN_FLASH = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-flash.png");
  BLOCKS_RED_HOVER_04 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-hover-04.png");
  BLOCKS_RED_PANIC_04 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-panic-04.png");
  GARBAGE_RIGHT_BOTTOM = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-right-bottom.png");
  GARBAGE_TOP_RIGHT_BOTTOM = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-top-right-bottom.png");
  BLOCKS_BLUE_PANIC_04 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-panic-04.png");
  //        EYE_SURPRISE = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("eye-surprise.png");
  BLOCKS_GREEN_LAND_02 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-land-02.png");
  GARBAGE_TOP_BOTTOM = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-top-bottom.png");
  BLOCKS_GREEN_COMPRESSED_02 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-compressed-02.png");
  BLOCKS_PURPLE_PANIC_04 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-panic-04.png");
  GARBAGE_LEFT = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-left.png");
  CURSOR_02 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("cursor-02.png");
  BLOCKS_PURPLE_HOVER_03 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-hover-03.png");
  BLOCKS_YELLOW_COMPRESSED_03 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-compressed-03.png");
  BLOCKS_YELLOW_PANIC_04 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-panic-04.png");
  GARBAGE_PLAIN = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-plain.png");
  BLOCKS_RED_HOVER_01 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-hover-01.png");
  BLOCKS_BLUE_COMPRESSED_04 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-compressed-04.png");
  BLOCKS_PURPLE_IDLE = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-idle.png");
  BLOCKS_PURPLE_HOVER_04 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-hover-04.png");
  BLOCKS_PURPLE_PANIC_02 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-panic-02.png");
  BLOCKS_GREEN_COMPRESSED_03 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-compressed-03.png");
  BLOCKS_RED_IDLE = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-idle.png");
  BLOCKS_YELLOW_HOVER_01 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-hover-01.png");
  BLOCKS_PURPLE_LAND_01 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-land-01.png");
  BLOCKS_PURPLE_COMPRESSED_04 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-compressed-04.png");
  BLOCKS_YELLOW_COMPRESSED_01 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-compressed-01.png");
  BLOCKS_PURPLE_COMPRESSED_02 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-compressed-02.png");
  BLOCKS_RED_COMPRESSED_01 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-compressed-01.png");
  BLOCKS_RED_HOVER_02 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-hover-02.png");
  GARBAGE_TOP_LEFT = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-top-left.png");
  BLOCKS_PURPLE_COMPRESSED_03 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-compressed-03.png");
  BLOCKS_RED_COMPRESSED_04 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-compressed-04.png");
  GARBAGE_TOP_LEFT_BOTTOM = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-top-left-bottom.png");
  BLOCKS_YELLOW_IDLE = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-idle.png");
  BLOCKS_PURPLE_LAND_02 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-land-02.png");
  BLOCKS_PURPLE_HAPPY = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-happy.png");
  BLOCKS_BLUE_COMPRESSED_03 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-compressed-03.png");
  BLOCKS_BLUE_HOVER_03 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-hover-03.png");
  GARBAGE_RIGHT = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-right.png");
  BLOCKS_RED_PANIC_02 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-panic-02.png");
  BLOCKS_GREEN_HAPPY = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-happy.png");
  BLOCKS_GREEN_PANIC_02 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-panic-02.png");
  BLOCKS_YELLOW_LAND_02 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-land-02.png");
  BLOCKS_BLUE_HOVER_02 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-hover-02.png");
  BLOCKS_RED_HOVER_03 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-hover-03.png");
  BLOCKS_GREEN_LAND_01 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-land-01.png");
  BLOCKS_BLUE_IDLE = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-idle.png");
  BLOCKS_RED_HAPPY = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-happy.png");
  BLOCKS_YELLOW_HOVER_04 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-hover-04.png");
  GARBAGE_SINGLE = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-single.png");
  //        EYE = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("eye.png");
  BLOCKS_GREEN_PANIC_03 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-panic-03.png");
  GARBAGE_LEFT_BOTTOM = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-left-bottom.png");
  BLOCKS_BLUE_PANIC_03 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-panic-03.png");
  //        LOSE = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("EndPopUp-Lose.png");
  BLOCKS_GREEN_HOVER_02 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-hover-02.png");
  BLOCKS_YELLOW_PANIC_03 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-panic-03.png");
  BLOCKS_PURPLE_FLASH = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-flash.png");
  BLOCKS_BLUE_COMPRESSED_01 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-compressed-01.png");
  BLOCKS_GREEN_COMPRESSED_04 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-compressed-04.png");
  BLOCKS_RED_LAND_01 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-land-01.png");
  BLOCKS_YELLOW_COMPRESSED_04 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-compressed-04.png");
  BLOCKS_RED_COMPRESSED_03 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-compressed-03.png");
  GARBAGE_BOTTOM = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-bottom.png");
  BLOCKS_GREEN_PANIC_04 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-panic-04.png");
  BLOCKS_RED_COMPRESSED_02 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-compressed-02.png");
  BLOCKS_BLUE_HOVER_04 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-hover-04.png");
  BLOCKS_YELLOW_PANIC_01 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-panic-01.png");
  BLOCKS_GREEN_HOVER_04 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-hover-04.png");
  BLOCKS_GREEN_HOVER_01 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-hover-01.png");
  BLOCKS_BLUE_LAND_02 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-land-02.png");
  BLOCKS_YELLOW_FLASH = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-flash.png");
  BLOCKS_YELLOW_LAND_01 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-land-01.png");
  BLOCKS_PURPLE_COMPRESSED_01 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-compressed-01.png");
  GARBAGE_TOP_RIGHT = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("garbage-top-right.png");
  BLOCKS_GREEN_HOVER_03 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-hover-03.png");
  BLOCKS_GREEN_PANIC_01 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-green-panic-01.png");
  BLOCKS_YELLOW_COMPRESSED_02 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-compressed-02.png");
  BLOCKS_YELLOW_PANIC_02 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-yellow-panic-02.png");
  BLOCKS_RED_FLASH = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-red-flash.png");
  BLOCKS_PURPLE_PANIC_03 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-panic-03.png");
  BLOCKS_PURPLE_HOVER_02 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-purple-hover-02.png");
  BLOCKS_BLUE_COMPRESSED_02 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-compressed-02.png");
  BLOCKS_BLUE_LAND_01 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blocks-blue-land-01.png");

  //  CCAnimation *animation = [CCAnimation animationWithFrames:[NSArray arrayWithObjects:BLOCKS_BLUE_COMPRESSED_01, BLOCKS_BLUE_COMPRESSED_02, nil]];

  //        [sprite runAction:[CCRepeatForever actionWithAction: [CCAnimate actionWithAnimation:animation restoreOriginalFrame:NO] ]];

  // Sprite grid
  //  CCSprite *background = [CCSprite spriteWithSpriteFrameName:@"bg.png");
  //  background.anchorPoint = ccp(0, 0);
  //  [batch addChild:background];

  // Initialize the grid
  for (int y = 0; y < FuriousBlocksCoreDefaults::PANEL_HEIGHT; y++) {
    for (int x = 0; x < FuriousBlocksCoreDefaults::PANEL_WIDTH; x++) {
      grid[x][y] = CCSprite::create(BLOCKS_YELLOW_LAND_02); // index[rand() % 8]
      grid[x][y]->setAnchorPoint(ccp(0, 0));
      grid[x][y]->setVisible(true);
      batch->addChild(grid[x][y]);
    }
  }

  //  std::thread t1(call_from_thread);
  //  t1.join();

  // Start the core
  //  ThreadExecutor<FuriousBlocksCore> executor;
  //  tbb::tbb_thread t(executor, core);

  tick = 0;

  // Start rendering
  schedule(schedule_selector(PanelScene::update));

  return true;
}

void PanelScene::update(float dt) {
  core->onTick(tick++);
  GameSituation *gs = core->gameSituation;
  PanelSituation *ps = gs->playerIdToPanelSituation[123];

  for (int y = 0; y < FuriousBlocksCoreDefaults::PANEL_HEIGHT; y++) {
    for (int x = 0; x < FuriousBlocksCoreDefaults::PANEL_WIDTH; x++) {
      BlockSituation *current = ps->blockSituations[x][y];
      if (current == nullptr) {
        grid[x][y]->setVisible(false);
        continue;
      }
      grid[x][y]->setPosition(ccp(x * 96, y * 96 + ps->scrollingOffset * 96  / 16));
      grid[x][y]->setVisible(true);
      CCSpriteFrame *frame = getBlockFrame(current, tick, false, false);
      if (frame != nullptr) {
        grid[x][y]->setDisplayFrame(frame);
      }
    }
  }
}

CCSpriteFrame *PanelScene::getBlockFrame(BlockSituation *blockSituation, int64_t tick, bool compressed, bool panicking) {
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
      }
    case BlockState::REVEALING:
      return GARBAGE_BLINK;

    case BlockState::AIRBOUNCING:
      switch (type) {
        case BlockType::YELLOW:
          return BLOCKS_YELLOW_HOVER_01;
          //                        return YELLOW_AIRBOUNCING.keyFrames[YELLOW_AIRBOUNCING.keyFrames.length - blockSituation.getStateTick()];
        case BlockType::GREEN:
          return BLOCKS_GREEN_HOVER_01;
          //                        return GREEN_AIRBOUNCING.keyFrames[GREEN_AIRBOUNCING.keyFrames.length - blockSituation.getStateTick()];
        case BlockType::RED:
          return BLOCKS_RED_HOVER_01;
          //                        return RED_AIRBOUNCING.keyFrames[RED_AIRBOUNCING.keyFrames.length - blockSituation.getStateTick()];
        case BlockType::PURPLE:
          return BLOCKS_PURPLE_HOVER_01;
          //                        return PURPLE_AIRBOUNCING.keyFrames[PURPLE_AIRBOUNCING.keyFrames.length - blockSituation.getStateTick()];
        case BlockType::BLUE:
          return BLOCKS_BLUE_HOVER_01;
          //                        return BLUE_AIRBOUNCING.keyFrames[BLUE_AIRBOUNCING.keyFrames.length - blockSituation.getStateTick()];
      }

      //      case DONE_FALLING:
      //        switch (type) {
      //          case YELLOW:
      //            animations.put(blockSituation.getId(), new AnimationContext(YELLOW_LANDING, tick));
      //            break;
      //          case BLUE:
      //            animations.put(blockSituation.getId(), new AnimationContext(BLUE_LANDING, tick));
      //            break;
      //          case PURPLE:
      //            animations.put(blockSituation.getId(), new AnimationContext(PURPLE_LANDING, tick));
      //            break;
      //          case RED:
      //            animations.put(blockSituation.getId(), new AnimationContext(RED_LANDING, tick));
      //            break;
      //          case GREEN:
      //            animations.put(blockSituation.getId(), new AnimationContext(GREEN_LANDING, tick));
      //            break;
      //          case GARBAGE:
      //          case INVISIBLE:
      //            break;
      //        }
      //        //$FALL-THROUGH$

    case BlockState::BLINKING:
      if ((tick % 2) != 0) {
        switch (type) {
          case BlockType::YELLOW:
            return BLOCKS_YELLOW_FLASH;
          case BlockType::GREEN:
            return BLOCKS_GREEN_FLASH;
          case BlockType::RED:
            return BLOCKS_RED_FLASH;
          case BlockType::PURPLE:
            return BLOCKS_PURPLE_FLASH;
          case BlockType::BLUE:
            return BLOCKS_BLUE_FLASH;
          case BlockType::GARBAGE:
            return GARBAGE_BLINK;
          case BlockType::INVISIBLE:
            break;
        }
      }
      //$FALL-THROUGH$

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
      //                if (currentAnimationContext != null) {
      //                    TextureRegion region = currentAnimationContext.getKeyFrame(tick);
      //                    if (region != null) {
      //                        return region;
      //                    }
      //                    animations.remove(blockSituation.getId());
      //                }
      switch (type) {
        case BlockType::YELLOW:
          if (compressed && state == BlockState:: IDLE) {
            return BLOCKS_YELLOW_COMPRESSED_01;
            //                            return YELLOW_COMPRESSING.keyFrames[((int) (tick % YELLOW_COMPRESSING.keyFrames.length))];
          }
          if (panicking && state == BlockState::IDLE) {
            return BLOCKS_YELLOW_PANIC_01;
            //                            return YELLOW_PANICKING.keyFrames[((int) (tick % YELLOW_PANICKING.keyFrames.length))];
          }
          return BLOCKS_YELLOW_IDLE;
        case BlockType::GREEN:
          if (compressed && state == BlockState::IDLE) {
            return BLOCKS_GREEN_COMPRESSED_01;
            //                            return GREEN_COMPRESSING.keyFrames[((int) (tick % GREEN_COMPRESSING.keyFrames.length))];
          }
          if (panicking && state == BlockState::IDLE) {
            return BLOCKS_GREEN_PANIC_01;
            //                            return GREEN_PANICKING.keyFrames[((int) (tick % GREEN_PANICKING.keyFrames.length))];
          }
          return BLOCKS_GREEN_IDLE;
        case BlockType::RED:
          if (compressed && state == BlockState::IDLE) {
            return BLOCKS_RED_COMPRESSED_01;
            //                            return RED_COMPRESSING.keyFrames[((int) (tick % RED_COMPRESSING.keyFrames.length))];
          }
          if (panicking && state == BlockState::IDLE) {
            return BLOCKS_RED_PANIC_01;
            //                            return RED_PANICKING.keyFrames[((int) (tick % RED_PANICKING.keyFrames.length))];
          }
          return BLOCKS_RED_IDLE;
        case BlockType::PURPLE:
          if (compressed && state == BlockState::IDLE) {
            return BLOCKS_PURPLE_COMPRESSED_01;
            //                            return PURPLE_COMPRESSING.keyFrames[((int) (tick % PURPLE_COMPRESSING.keyFrames.length))];
          }
          if (panicking && state == BlockState::IDLE) {
            return BLOCKS_PURPLE_PANIC_01;
            //                            return PURPLE_PANICKING.keyFrames[((int) (tick % PURPLE_PANICKING.keyFrames.length))];
          }
          return BLOCKS_PURPLE_IDLE;
        case BlockType::BLUE:
          if (compressed && state == BlockState::IDLE) {
            return BLOCKS_BLUE_COMPRESSED_01;
            //                            return BLUE_COMPRESSING.keyFrames[((int) (tick % BLUE_COMPRESSING.keyFrames.length))];
          }
          if (panicking && state == BlockState::IDLE) {
            return BLOCKS_BLUE_PANIC_01;
            //                            return BLUE_PANICKING.keyFrames[((int) (tick % BLUE_PANICKING.keyFrames.length))];
          }
          return BLOCKS_BLUE_IDLE;
        case BlockType::GARBAGE:
          //                        final int garbageBlockType = blockSituation.getGarbageBlockType();
          //                        switch (garbageBlockType) {
          //                            case GarbageBlockType.DOWN:
          //                                return GARBAGE_BOTTOM;
          //                            case GarbageBlockType.DOWNLEFT:
          //                                return GARBAGE_BOTTOMLEFT;
          //                            case GarbageBlockType.DOWNRIGHT:
          //                                return GARBAGE_BOTTOMRIGHT;
          //                            case GarbageBlockType.LEFT:
          //                                return GARBAGE_LEFT;
          //                            case GarbageBlockType.PLAIN:
          //                                return GARBAGE_PLAIN;
          //                            case GarbageBlockType.RIGHT:
          //                                return GARBAGE_RIGHT;
          //                            case GarbageBlockType.UP:
          //                                return GARBAGE_TOP;
          //                            case GarbageBlockType.UPDOWN:
          //                                return GARBAGE_TOPBOTTOM;
          //                            case GarbageBlockType.UPLEFT:
          //                                return GARBAGE_TOPLEFT;
          //                            case GarbageBlockType.UPLEFTDOWN:
          //                                return GARBAGE_TOPLEFTBOTTOM;
          //                            case GarbageBlockType.UPRIGHT:
          //                                return GARBAGE_TOPRIGHT;
          //                            case GarbageBlockType.UPRIGHTDOWN:
          //                                return GARBAGE_TOPRIGHTBOTTOM;
          //                            default:
          //                                throw new IllegalStateException("Undefined garbage block type: " + garbageBlockType);
          //                        }
          return GARBAGE_BLINK;
      }
    case BlockState::DONE_EXPLODING:
    case BlockState::TO_DELETE:
      //                animations.remove(blockSituation.getId());
      return nullptr;
  }

  return nullptr;
}


void PanelScene::menuCloseCallback(CCObject *pSender) {
  CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  exit(0);
#endif
}

//
//- (void)dealloc {
//    delete core;
//    delete player;
//    [[CCSpriteFrameCache sharedSpriteFrameCache] removeUnusedSpriteFrames];
//    [super dealloc];
//}
//@end
