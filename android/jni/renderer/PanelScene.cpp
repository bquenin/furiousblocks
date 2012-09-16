#include "PanelScene.h"
#include "GarbageBlockType.h"

USING_NS_CC;

PanelScene::PanelScene()
: tick(0)
, stateTime(0) {
}

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

void *PanelScene::game_draw_thread_callback(void *pVoid) {
  CCLOG("Hello World!");
  return nullptr;
}

// on "init" you need to initialize your instance
bool PanelScene::init() {
  if (!CCLayer::init()) {
    return false;
  }

  setTouchEnabled(true);

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

  YELLOW_PANICKING = new Animation(4.f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {BLOCKS_YELLOW_PANIC_01, BLOCKS_YELLOW_PANIC_02, BLOCKS_YELLOW_PANIC_03, BLOCKS_YELLOW_PANIC_04, BLOCKS_YELLOW_PANIC_03, BLOCKS_YELLOW_PANIC_02, BLOCKS_YELLOW_PANIC_01});
  BLUE_PANICKING = new Animation(4.f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {BLOCKS_BLUE_PANIC_01, BLOCKS_BLUE_PANIC_02, BLOCKS_BLUE_PANIC_03, BLOCKS_BLUE_PANIC_04, BLOCKS_BLUE_PANIC_03, BLOCKS_BLUE_PANIC_02, BLOCKS_BLUE_PANIC_01});
  RED_PANICKING = new Animation(4.f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {BLOCKS_RED_PANIC_01, BLOCKS_RED_PANIC_02, BLOCKS_RED_PANIC_03, BLOCKS_RED_PANIC_04, BLOCKS_RED_PANIC_03, BLOCKS_RED_PANIC_02, BLOCKS_RED_PANIC_01});
  GREEN_PANICKING = new Animation(4.f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {BLOCKS_GREEN_PANIC_01, BLOCKS_GREEN_PANIC_02, BLOCKS_GREEN_PANIC_03, BLOCKS_GREEN_PANIC_04, BLOCKS_GREEN_PANIC_03, BLOCKS_GREEN_PANIC_02, BLOCKS_GREEN_PANIC_01});
  PURPLE_PANICKING = new Animation(4.f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {BLOCKS_PURPLE_PANIC_01, BLOCKS_PURPLE_PANIC_02, BLOCKS_PURPLE_PANIC_03, BLOCKS_PURPLE_PANIC_04, BLOCKS_PURPLE_PANIC_03, BLOCKS_PURPLE_PANIC_02, BLOCKS_PURPLE_PANIC_01});

  YELLOW_COMPRESSING = new Animation(4.f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {BLOCKS_YELLOW_COMPRESSED_01, BLOCKS_YELLOW_COMPRESSED_02, BLOCKS_YELLOW_COMPRESSED_03, BLOCKS_YELLOW_COMPRESSED_04});
  BLUE_COMPRESSING = new Animation(4.f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {BLOCKS_BLUE_COMPRESSED_01, BLOCKS_BLUE_COMPRESSED_02, BLOCKS_BLUE_COMPRESSED_03, BLOCKS_BLUE_COMPRESSED_04});
  RED_COMPRESSING = new Animation(4.f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {BLOCKS_RED_COMPRESSED_01, BLOCKS_RED_COMPRESSED_02, BLOCKS_RED_COMPRESSED_03, BLOCKS_RED_COMPRESSED_04});
  GREEN_COMPRESSING = new Animation(4.f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {BLOCKS_GREEN_COMPRESSED_01, BLOCKS_GREEN_COMPRESSED_02, BLOCKS_GREEN_COMPRESSED_03, BLOCKS_GREEN_COMPRESSED_04});
  PURPLE_COMPRESSING = new Animation(4.f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {BLOCKS_PURPLE_COMPRESSED_01, BLOCKS_PURPLE_COMPRESSED_02, BLOCKS_PURPLE_COMPRESSED_03, BLOCKS_PURPLE_COMPRESSED_04});

  YELLOW_BLINKING = new Animation(1.f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {BLOCKS_YELLOW_FLASH, BLOCKS_YELLOW_IDLE});
  BLUE_BLINKING = new Animation(1.f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {BLOCKS_BLUE_FLASH, BLOCKS_BLUE_IDLE});
  RED_BLINKING = new Animation(1.f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {BLOCKS_RED_FLASH, BLOCKS_RED_IDLE});
  GREEN_BLINKING = new Animation(1.f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {BLOCKS_GREEN_FLASH, BLOCKS_GREEN_IDLE});
  PURPLE_BLINKING = new Animation(1.f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {BLOCKS_PURPLE_FLASH, BLOCKS_PURPLE_IDLE});
  GARBAGE_BLINKING = new Animation(1.f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {GARBAGE_BLINK, GARBAGE_PLAIN});

  CURSOR = new Animation(16.f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {CURSOR_01, CURSOR_02, CURSOR_03, CURSOR_02});

  // Background
  //  CCSprite *background = CCSprite::createWithSpriteFrameName("bg.png");
  //  background->setAnchorPoint(ccp(0, 0));
  //  batch->addChild(background);

  // Initialize the grid
  for (int y = 0; y < FuriousBlocksCoreDefaults::PANEL_HEIGHT; y++) {
    for (int x = 0; x < FuriousBlocksCoreDefaults::PANEL_WIDTH; x++) {
      grid[x][y] = CCSprite::createWithSpriteFrame(GARBAGE_PLAIN);
      grid[x][y]->setAnchorPoint(ccp(0, 0));
      grid[x][y]->setVisible(false);
      batch->addChild(grid[x][y]);
    }
  }

  // Cursor
  cursor = CCSprite::createWithSpriteFrameName("cursor-01.png");
  cursor->setAnchorPoint(ccp(0, 0));
  batch->addChild(cursor);

  // Game initialization
  core = new FuriousBlocksCore(0);

  // Player initialization
  player = new Player();
  core->addPlayer(player);

  pthread_t t1;
  pthread_create(&t1, NULL, PanelScene::game_draw_thread_callback, this);
  pthread_join(t1, NULL);

  //  std::thread t1(call_from_thread);
  //  t1.join();

  // Start the core
  //  ThreadExecutor<FuriousBlocksCore> executor;
  //  tbb::tbb_thread t(executor, core);

  // Start rendering
  schedule(schedule_selector(PanelScene::update));

  return true;
}

void PanelScene::update(float dt) {
  stateTime += dt;
  core->onTick(tick++);
  std::shared_ptr<GameSituation> gs(core->gameSituation);
  auto ps = gs->playerIdToPanelSituation[123];

  // Blocks
  for (int y = 0; y < FuriousBlocksCoreDefaults::PANEL_HEIGHT; y++) {
    for (int x = 0; x < FuriousBlocksCoreDefaults::PANEL_WIDTH; x++) {
      BlockSituation *current = ps->blockSituations[x][y];
      if (current == nullptr) {
        grid[x][y]->setVisible(false);
        continue;
      }
      grid[x][y]->setPosition(ccp(17 + x * 48, 10 + y * 48 + ps->scrollingOffset * 48 / 16));
      CCSpriteFrame *frame = getBlockFrame(current, stateTime, false, true);
      if (frame != nullptr) {
        grid[x][y]->setDisplayFrame(frame);
        grid[x][y]->setVisible(true);
      } else {
        grid[x][y]->setVisible(false);
      }
    }
  }

  // Cursor
  cursor->setPosition(ccp(ps->cursorPosition.x * 48, ps->cursorPosition.y * 48 + ps->scrollingOffset * 48 / 16 - 8));
  cursor->setDisplayFrame(CURSOR->getKeyFrame(stateTime, true));

}

CCSpriteFrame *PanelScene::getBlockFrame(BlockSituation *blockSituation, float stateTime, bool compressed, bool panicking) {
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
            animation = new NonLoopingAnimation(stateTime, 4.0f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {BLOCKS_YELLOW_HOVER_01, BLOCKS_YELLOW_HOVER_02, BLOCKS_YELLOW_HOVER_03, BLOCKS_YELLOW_HOVER_04, BLOCKS_YELLOW_HOVER_03, BLOCKS_YELLOW_HOVER_02, BLOCKS_YELLOW_HOVER_01});
            break;
          case BlockType:: BLUE:
            animation = new NonLoopingAnimation(stateTime, 4.0f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {BLOCKS_BLUE_HOVER_01, BLOCKS_BLUE_HOVER_02, BLOCKS_BLUE_HOVER_03, BLOCKS_BLUE_HOVER_04, BLOCKS_BLUE_HOVER_03, BLOCKS_BLUE_HOVER_02, BLOCKS_BLUE_HOVER_01});
            break;
          case BlockType:: PURPLE:
            animation = new NonLoopingAnimation(stateTime, 4.0f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {BLOCKS_PURPLE_HOVER_01, BLOCKS_PURPLE_HOVER_02, BLOCKS_PURPLE_HOVER_03, BLOCKS_PURPLE_HOVER_04, BLOCKS_PURPLE_HOVER_03, BLOCKS_PURPLE_HOVER_02, BLOCKS_PURPLE_HOVER_01});
            break;
          case BlockType:: RED:
            animation = new NonLoopingAnimation(stateTime, 4.0f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {BLOCKS_RED_HOVER_01, BLOCKS_RED_HOVER_02, BLOCKS_RED_HOVER_03, BLOCKS_RED_HOVER_04, BLOCKS_RED_HOVER_03, BLOCKS_RED_HOVER_02, BLOCKS_RED_HOVER_01});
            break;
          case BlockType:: GREEN:
            animation = new NonLoopingAnimation(stateTime, 4.0f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {BLOCKS_GREEN_HOVER_01, BLOCKS_GREEN_HOVER_02, BLOCKS_GREEN_HOVER_03, BLOCKS_GREEN_HOVER_04, BLOCKS_GREEN_HOVER_03, BLOCKS_GREEN_HOVER_02, BLOCKS_GREEN_HOVER_01});
            break;
        }
        animations[blockSituation->id] = animation;
        return animation->getKeyFrame(stateTime);
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
      if (blockSituation->justLand && state == BlockState:: IDLE && type != BlockType:: GARBAGE && type != BlockType:: TUTORIAL) {
        NonLoopingAnimation *animation = nullptr;
        switch (type) {
          case BlockType:: YELLOW:
            animation = new NonLoopingAnimation(stateTime, 4.0f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {BLOCKS_YELLOW_LAND_01, BLOCKS_YELLOW_IDLE, BLOCKS_YELLOW_LAND_02, BLOCKS_YELLOW_IDLE});
            break;
          case BlockType:: BLUE:
            animation = new NonLoopingAnimation(stateTime, 4.0f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {BLOCKS_BLUE_LAND_01, BLOCKS_BLUE_IDLE, BLOCKS_BLUE_LAND_02, BLOCKS_BLUE_IDLE});
            break;
          case BlockType:: PURPLE:
            animation = new NonLoopingAnimation(stateTime, 4.0f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {BLOCKS_PURPLE_LAND_01, BLOCKS_PURPLE_IDLE, BLOCKS_PURPLE_LAND_02, BLOCKS_PURPLE_IDLE});
            break;
          case BlockType:: RED:
            animation = new NonLoopingAnimation(stateTime, 4.0f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {BLOCKS_RED_LAND_01, BLOCKS_RED_IDLE, BLOCKS_RED_LAND_02, BLOCKS_RED_IDLE});
            break;
          case BlockType:: GREEN:
            animation = new NonLoopingAnimation(stateTime, 4.0f / FuriousBlocksCoreDefaults::CORE_FREQUENCY, {BLOCKS_GREEN_LAND_01, BLOCKS_GREEN_IDLE, BLOCKS_GREEN_LAND_02, BLOCKS_GREEN_IDLE});
            break;
        }
        delete animations[blockSituation->id];
        animations[blockSituation->id] = animation;
        return animation->getKeyFrame(stateTime);
      }
      if (currentAnimation != nullptr) {
        if (currentAnimation->isAnimationFinished(stateTime)) {
          delete animations[blockSituation->id];
          animations.erase(blockSituation->id);
        } else {
          return currentAnimation->getKeyFrame(stateTime);
        }
      }
      switch (type) {
        case BlockType::YELLOW:
          if (compressed && state == BlockState:: IDLE) {
            return YELLOW_COMPRESSING->getKeyFrame(stateTime, true);
          }
          if (panicking && state == BlockState:: IDLE) {
            return YELLOW_PANICKING->getKeyFrame(stateTime, true);
          }
          return state == BlockState:: BLINKING ? YELLOW_BLINKING->getKeyFrame(stateTime, true) : BLOCKS_YELLOW_IDLE;

        case BlockType:: GREEN:
          if (compressed && state == BlockState:: IDLE) {
            return GREEN_COMPRESSING->getKeyFrame(stateTime, true);
          }
          if (panicking && state == BlockState:: IDLE) {
            return GREEN_PANICKING->getKeyFrame(stateTime, true);
          }
          return state == BlockState::BLINKING ? GREEN_BLINKING->getKeyFrame(stateTime, true) : BLOCKS_GREEN_IDLE;
        case BlockType:: RED:
          if (compressed && state == BlockState:: IDLE) {
            return RED_COMPRESSING->getKeyFrame(stateTime, true);
          }
          if (panicking && state == BlockState::IDLE) {
            return RED_PANICKING->getKeyFrame(stateTime, true);
          }
          return state == BlockState::BLINKING ? RED_BLINKING->getKeyFrame(stateTime, true) : BLOCKS_RED_IDLE;
        case BlockType:: PURPLE:
          if (compressed && state == BlockState::IDLE) {
            return PURPLE_COMPRESSING->getKeyFrame(stateTime, true);
          }
          if (panicking && state == BlockState::IDLE) {
            return PURPLE_PANICKING->getKeyFrame(stateTime, true);
          }
          return state == BlockState::BLINKING ? PURPLE_BLINKING->getKeyFrame(stateTime, true) : BLOCKS_PURPLE_IDLE;
        case BlockType:: BLUE:
          if (compressed && state == BlockState::IDLE) {
            return BLUE_COMPRESSING->getKeyFrame(stateTime, true);
          }
          if (panicking && state == BlockState::IDLE) {
            return BLUE_PANICKING->getKeyFrame(stateTime, true);
          }
          return state == BlockState::BLINKING ? BLUE_BLINKING->getKeyFrame(stateTime, true) : BLOCKS_BLUE_IDLE;
        case BlockType::TUTORIAL:
          return GARBAGE_SINGLE;
        case BlockType::GARBAGE:
          if (state == BlockState:: BLINKING && GARBAGE_BLINKING->getKeyFrame(stateTime, true) == GARBAGE_BLINK) {
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

void PanelScene::onEnter() {
  CCDirector *pDirector = CCDirector::sharedDirector();
  pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
  CCLayer::onEnter();
}

void PanelScene::onExit() {
  CCDirector *pDirector = CCDirector::sharedDirector();
  pDirector->getTouchDispatcher()->removeDelegate(this);
  CCLayer::onExit();
}

bool PanelScene::ccTouchBegan(CCTouch *touch, CCEvent *event) {
  //  if (m_state != kPaddleStateUngrabbed) {
  //    return false;
  //  }
  //  if (!containsTouchLocation(touch)) {
  //    return false;
  //  }
  //
  //  m_state = kPaddleStateGrabbed;
  CCLOG("began");
  return true;
}


void PanelScene::ccTouchMoved(CCTouch *touch, CCEvent *event) {
  // If it weren't for the TouchDispatcher, you would need to keep a reference
  // to the touch from touchBegan and check that the current touch is the same
  // as that one.
  // Actually, it would be even more complicated since in the Cocos dispatcher
  // you get CCSets instead of 1 UITouch, so you'd need to loop through the set
  // in each touchXXX method.

  //  CCAssert(m_state == kPaddleStateGrabbed, L"Paddle - Unexpected state!");

  CCPoint touchPoint = touch->getLocation();

  CCLOG("x/y = %f/%f", touchPoint.x, touchPoint.y);

  //  setPosition(CCPointMake(touchPoint.x, getPosition().y));
}

void PanelScene::ccTouchEnded(CCTouch *touch, CCEvent *event) {
  CCLOG("end");
  //  CCAssert(m_state == kPaddleStateGrabbed, L"Paddle - Unexpected state!");
  //
  //  m_state = kPaddleStateUngrabbed;
}
