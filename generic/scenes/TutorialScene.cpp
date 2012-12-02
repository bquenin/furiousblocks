//
// Created by bquenin on 11/2/12.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "TutorialScene.h"
#include "StarNumber.h"
#include "easing_back.hpp"
#include "easing_bounce.hpp"
#include "easing_linear.hpp"
#include "easing_quad.hpp"
#include "tweener_sequence.hpp"
#include "TypeTextAction.h"
#include "PauseAction.h"
#include "CursorAction.h"
#include "SetBlocksAction.h"
#include "SimpleAudioEngine.h"
#include "Assets.h"
#include "AppDelegate.h"
#include <boost/bind.hpp>

std::vector<std::vector<BlockType>> TutorialScene::empty = {
    {BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL}
};

std::vector<std::vector<BlockType>> TutorialScene::combo4and5 = {
    {BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL},
    {BlockType::YELLOW, BlockType::RED, static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::RED, BlockType::YELLOW},
    {BlockType::YELLOW, BlockType::RED, static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::RED, BlockType::YELLOW},
    {BlockType::RED, BlockType::GREEN, static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::GREEN, BlockType::RED},
    {static_cast<BlockType>(-1), BlockType::RED, static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::RED, static_cast<BlockType>(-1)},
    {static_cast<BlockType>(-1), static_cast<BlockType>(-1), static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::RED, static_cast<BlockType>(-1)}
};

std::vector<std::vector<BlockType>> TutorialScene::combo6and10 = {
    {BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL}, //
    {BlockType::YELLOW, BlockType::RED, static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::RED, BlockType::YELLOW}, //
    {BlockType::RED, BlockType::YELLOW, static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::RED, BlockType::YELLOW}, //
    {BlockType::YELLOW, BlockType::RED, static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::YELLOW, BlockType::RED}, //
    {static_cast<BlockType>(-1), static_cast<BlockType>(-1), static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::RED, BlockType::YELLOW}, //
    {static_cast<BlockType>(-1), static_cast<BlockType>(-1), static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::RED, BlockType::YELLOW}
};

std::vector<std::vector<BlockType>> TutorialScene::chainx2 = { //
    {BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL}, //
    {static_cast<BlockType>(-1), BlockType::GREEN, BlockType::RED, BlockType::RED, static_cast<BlockType>(-1), BlockType::RED}, //
    {static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::GREEN, BlockType::GREEN, static_cast<BlockType>(-1), static_cast<BlockType>(-1)}
};

std::vector<std::vector<BlockType>> TutorialScene::chainx3 = { //
    {BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL}, //
    {BlockType::PURPLE, BlockType::GREEN, BlockType::RED, BlockType::RED, static_cast<BlockType>(-1), BlockType::RED}, //
    {static_cast<BlockType>(-1), BlockType::PURPLE, BlockType::GREEN, BlockType::GREEN, static_cast<BlockType>(-1), static_cast<BlockType>(-1)}, //
    {static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::PURPLE, static_cast<BlockType>(-1), static_cast<BlockType>(-1), static_cast<BlockType>(-1)}
};

std::vector<std::vector<BlockType>> TutorialScene::etc4ChainsPanel = { //
    {BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL}, //
    {BlockType::BLUE, BlockType::BLUE, BlockType::RED, BlockType::RED, BlockType::YELLOW, BlockType::TUTORIAL}, //
    {BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::BLUE, BlockType::GREEN, BlockType::PURPLE, BlockType::PURPLE}, //
    {BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::YELLOW, BlockType::RED, BlockType::RED, BlockType::TUTORIAL}, //
    {BlockType::TUTORIAL, BlockType::BLUE, BlockType::PURPLE, BlockType::PURPLE, BlockType::YELLOW, BlockType::TUTORIAL}, //
    {BlockType::BLUE, BlockType::TUTORIAL, BlockType::YELLOW, BlockType::GREEN, BlockType::YELLOW, BlockType::TUTORIAL}, //
    {BlockType::TUTORIAL, BlockType::BLUE, BlockType::YELLOW, BlockType::GREEN, BlockType::RED, BlockType::TUTORIAL}, //
    {BlockType::TUTORIAL, BlockType::PURPLE, BlockType::RED, BlockType::PURPLE, BlockType::TUTORIAL, BlockType::TUTORIAL} //
};

TutorialScene::TutorialScene()
: inputState (InputState::untouched)
, overlayEnabled (false) {
  gameRunning = true;
}

TutorialScene::~TutorialScene() {
  script.empty();
}

void TutorialScene::setOverlay(QuitOverlay *quitOverlay) {
  this->quitOverlay = quitOverlay;
}

CCScene *TutorialScene::scene() {
  CCScene *scene = CCScene::create();
  TutorialScene *layer = TutorialScene::create();
  scene->addChild(layer);
  QuitOverlay *quitOverlay = QuitOverlay::create();
  scene->addChild(quitOverlay);
  layer->setOverlay(quitOverlay);
  return scene;
}

bool TutorialScene::init() {
  if (!CCLayer::init()) {
    return false;
  }

  AbstractPanelScene::init();

  setTouchEnabled(true);

  CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("tutorial.mp3", true);

  // Cursor
  cursor = CCSprite::createWithSpriteFrameName("cursor-01.png");
  cursor->autorelease();
  cursor->setAnchorPoint(ccp(0, 0));
  batch->addChild(cursor);

  cocos2d::CCSize size = cocos2d::CCDirector::sharedDirector()->getWinSize();

  textBox = cocos2d::CCLabelBMFont::create("textToType", "coopblack32.fnt", 500, kCCTextAlignmentLeft);
  textBox->autorelease();
  textBox->setAnchorPoint(ccp(0, 1));
  textBox->setPosition(ccp(64, 800));
  addChild(textBox);

  // Game initialization
  core = new FuriousBlocksCore(2064, this);
  core->initialBlockTypes[5][2] = static_cast<BlockType >(-1);
  core->initialBlockTypes[5][3] = static_cast<BlockType >(-1);
  core->initialBlockTypes[4][3] = static_cast<BlockType >(-1);

  // Player initialization
  tutorialPlayer = new TutorialPlayer();
  core->addPlayer(tutorialPlayer);

  Panel &tutorialPanel = *core->playerToPanel[tutorialPlayer];
  tutorialPanel.scrollingEnabled = false;

  // Tutorial script
  script.add(new TypeTextAction(.1f, "Hi!\nYou have to clear these blocks.", textToType));
  script.add(new PauseAction(1));
  script.add(new TypeTextAction(.1f, "It's made of blocks you can move horizontally.", textToType));
  script.add(new CursorAction(1.0f, tutorialPlayer, MoveType::CURSOR_DOWN));
  script.add(new TypeTextAction(.1f, "Slide horizontally with your finger to move them.", textToType));
  script.add(new CursorAction(.5f, tutorialPlayer, MoveType::BLOCK_SWITCH));
  script.add(new CursorAction(.5f, tutorialPlayer, MoveType::BLOCK_SWITCH));
  script.add(new CursorAction(.5f, tutorialPlayer, MoveType::BLOCK_SWITCH));
  script.add(new CursorAction(.5f, tutorialPlayer, MoveType::BLOCK_SWITCH));
  script.add(new CursorAction(.5f, tutorialPlayer, MoveType::BLOCK_SWITCH));
  script.add(new CursorAction(.5f, tutorialPlayer, MoveType::BLOCK_SWITCH));

  script.add(new TypeTextAction(.1f, "You can make them fall to fill in holes.", textToType));
  script.add(new CursorAction(.05f, tutorialPlayer, MoveType::CURSOR_RIGHT));
  script.add(new CursorAction(.05f, tutorialPlayer, MoveType::BLOCK_SWITCH));
  script.add(new CursorAction(.05f, tutorialPlayer, MoveType::CURSOR_RIGHT));
  script.add(new CursorAction(.05f, tutorialPlayer, MoveType::BLOCK_SWITCH));

  script.add(new TypeTextAction(.1f, "Align 3 blocks horizontally or vertically...", textToType));
  script.add(new CursorAction(.5f, tutorialPlayer, MoveType::CURSOR_LEFT));
  script.add(new CursorAction(.5f, tutorialPlayer, MoveType::CURSOR_LEFT));
  script.add(new CursorAction(.05f, tutorialPlayer, MoveType::CURSOR_LEFT));
  script.add(new CursorAction(.05f, tutorialPlayer, MoveType::CURSOR_LEFT));
  script.add(new CursorAction(.05f, tutorialPlayer, MoveType::BLOCK_SWITCH));
  script.add(new TypeTextAction(.1f, "... to clear them.", textToType));
  script.add(new PauseAction(1));
  script.add(new CursorAction(.05f, tutorialPlayer, MoveType::CURSOR_RIGHT));
  script.add(new CursorAction(.05f, tutorialPlayer, MoveType::BLOCK_SWITCH));
  script.add(new CursorAction(.05f, tutorialPlayer, MoveType::CURSOR_LEFT));
  script.add(new CursorAction(.05f, tutorialPlayer, MoveType::BLOCK_SWITCH));
  script.add(new PauseAction(1));

  script.add(new TypeTextAction(.1f, "If you slide vertically with your finger.", textToType));
  script.add(new PauseAction(1));
  script.add(new TypeTextAction(.1f, "It raises the stack.", textToType));
  script.add(new CursorAction(.1f, tutorialPlayer, MoveType::LIFT));
  script.add(new PauseAction(.5f));
  script.add(new CursorAction(.1f, tutorialPlayer, MoveType::LIFT));
  script.add(new PauseAction(.5f));
  script.add(new CursorAction(.1f, tutorialPlayer, MoveType::LIFT));
  script.add(new PauseAction(.5f));
  script.add(new CursorAction(.1f, tutorialPlayer, MoveType::LIFT));
  script.add(new PauseAction(.5f));
  script.add(new TypeTextAction(.1f, "Don't raise it too much though, or ...", textToType));
  script.add(new CursorAction(.1f, tutorialPlayer, MoveType::LIFT));
  script.add(new PauseAction(.5f));
  script.add(new CursorAction(.1f, tutorialPlayer, MoveType::LIFT));
  script.add(new PauseAction(.5f));
  script.add(new TypeTextAction(.1f, "... blocks start panicking ...", textToType));
  script.add(new CursorAction(.1f, tutorialPlayer, MoveType::LIFT));
  script.add(new PauseAction(1));
  script.add(new TypeTextAction(.1f, "... and eventually the game is over.", textToType));
  script.add(new PauseAction(2));

  script.add(new SetBlocksAction(1, tutorialPanel, empty));
  script.add(new TypeTextAction(.1f, "Now let's have a look at combos and chains.", textToType));
  script.add(new SetBlocksAction(1, tutorialPanel, combo4and5));
  script.add(new TypeTextAction(.1f, "A combo is triggered when you clear at least 4 blocks.", textToType));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::CURSOR_DOWN));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::CURSOR_DOWN));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::CURSOR_DOWN));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::CURSOR_DOWN));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::CURSOR_DOWN));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::CURSOR_DOWN));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::BLOCK_SWITCH));
  script.add(new TypeTextAction(.1f, "Clear 4!", textToType));
  script.add(new PauseAction(1));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::CURSOR_RIGHT));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::CURSOR_RIGHT));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::CURSOR_RIGHT));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::CURSOR_RIGHT));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::BLOCK_SWITCH));
  script.add(new TypeTextAction(.1f, "Clear 5!", textToType));
  script.add(new PauseAction(2));
  script.add(new SetBlocksAction(0.01f, tutorialPanel, combo6and10));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::CURSOR_LEFT));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::CURSOR_LEFT));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::CURSOR_LEFT));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::CURSOR_LEFT));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::CURSOR_DOWN));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::BLOCK_SWITCH));
  script.add(new TypeTextAction(.1f, "Clear 6!", textToType));
  script.add(new PauseAction(1));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::CURSOR_RIGHT));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::CURSOR_RIGHT));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::CURSOR_RIGHT));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::CURSOR_RIGHT));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::CURSOR_UP));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::BLOCK_SWITCH));
  script.add(new TypeTextAction(.1f, "Clear 10!", textToType));
  script.add(new PauseAction(2));

  script.add(new SetBlocksAction(1, tutorialPanel, empty));
  script.add(new TypeTextAction(.1f, "Now on to chains.", textToType));
  script.add(new PauseAction(1));
  script.add(new SetBlocksAction(0.01f, tutorialPanel, chainx2));
  script.add(new TypeTextAction(.1f, "Chains are triggered when a clearing is done with blocks ...", textToType));
  script.add(new PauseAction(1));
  script.add(new TypeTextAction(.1f, "... falling from a previous clearing.", textToType));
  script.add(new PauseAction(1));
  script.add(new TypeTextAction(.1f, "Chain x2", textToType));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::CURSOR_DOWN));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::CURSOR_DOWN));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::BLOCK_SWITCH));
  script.add(new PauseAction(4));
  script.add(new SetBlocksAction(0.01f, tutorialPanel, chainx3));
  script.add(new TypeTextAction(.1f, "Chain x3", textToType));
  script.add(new CursorAction(.02f, tutorialPlayer, MoveType::BLOCK_SWITCH));
  script.add(new PauseAction(5));

  script.add(new TypeTextAction(.1f, "This closes the tutorial.\nGo play to practice!", textToType));
  script.add(new PauseAction(1));

  // Start scheduling
  schedule(schedule_selector(TutorialScene::update));

  return true;
}

void TutorialScene::update(float dt) {
  // Situation rendering
  Panel const &panel = *core->playerToPanel[tutorialPlayer];

  // Blocks
  for (int y = 0; y < FuriousBlocksCoreDefaults::PANEL_HEIGHT + 1; y++) {
    for (int x = 0; x < FuriousBlocksCoreDefaults::PANEL_WIDTH; x++) {
      Block *current = panel.blocks[x][y];
      if (current == nullptr) {
        grid[x][y]->setVisible(false);
        continue;
      }

      CCSpriteFrame *frame = AppDelegate::assets.getBlockFrame(current, tick, panel.blocks[x][FuriousBlocksCoreDefaults::PANEL_HEIGHT] != nullptr, panel.blocks[x][FuriousBlocksCoreDefaults::PANEL_HEIGHT - 1] != nullptr);
      if (frame == nullptr) {
        grid[x][y]->setVisible(false);
        continue;
      }

      if (!panel.isGameOver()) {
        grid[x][y]->setPosition(ccp(xOffset + x * Assets::TILE_SIZE, yOffset + y * Assets::TILE_SIZE + panel.scrollingDelta * Assets::TILE_SIZE / FuriousBlocksCoreDefaults::BLOCK_LOGICALHEIGHT));
      }
      grid[x][y]->setDisplayFrame(frame);
      grid[x][y]->setVisible(true);
      if (y == 0) {
        grid[x][y]->setColor(ccc3(0x50, 0x50, 0x50));
      }

    }
  }

  cursor->setPosition(ccp(panel.cursor->x * Assets::TILE_SIZE, -16 + (panel.cursor->y - 1) * Assets::TILE_SIZE + panel.scrollingDelta * Assets::TILE_SIZE / FuriousBlocksCoreDefaults::BLOCK_LOGICALHEIGHT));

  // Tweeners update
  tweeners.update(dt);

  // State time update
  stateTime += dt;

  textBox->setString(textToType.getText().c_str());

  // Core tick
  core->onTick(tick++);

  script.execute(stateTime);
}

void TutorialScene::onCombo(Combo *combo) {
  if (combo->size() > 3) {
    new StarNumber(this, xOffset + combo->x * Assets::TILE_SIZE, yOffset + combo->y * Assets::TILE_SIZE, Assets::format("%d", combo->size()), ccORANGE);
  }
  if (combo->skillChainLevel > 1) {
    new StarNumber(this, xOffset + combo->x * Assets::TILE_SIZE, yOffset + (combo->y + 1) * Assets::TILE_SIZE, Assets::format("x%d", combo->skillChainLevel), ccc3(255, 128, 128));
  }
}

void TutorialScene::onGameOver() {
  // Initialize tweeners
  for (int y = 0; y < FuriousBlocksCoreDefaults::PANEL_HEIGHT + 1; y++) {
    for (int x = 0; x < FuriousBlocksCoreDefaults::PANEL_WIDTH; x++) {
      if (y > 0) {
        tweeners.insert(claw::tween::single_tweener(grid[x][y]->getPositionY(), random() % 350 + Assets::designResolutionSize.height + yOffset + y * Assets::TILE_SIZE, 2, boost::bind(&CCNode::setPositionY, grid[x][y], _1), claw::tween::easing_bounce::ease_in));
      }
    }
  }
}

void TutorialScene::registerWithTouchDispatcher() {
  cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool TutorialScene::ccTouchBegan(CCTouch *touch, CCEvent *event) {
  if (inputState != InputState::untouched || quitOverlay->isVisible()) {
    return false;
  }
  inputState = InputState::touched;
  return true;
}

void TutorialScene::ccTouchEnded(CCTouch *touch, CCEvent *event) {
  inputState = InputState::untouched;
  quitOverlay->setVisible(true);
}

void TutorialScene::ccTouchMoved(CCTouch *touch, CCEvent *event) {
}
