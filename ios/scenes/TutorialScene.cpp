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
#include <boost/bind.hpp>

TutorialScene::TutorialScene() {
  gameRunning = true;
}

CCScene *TutorialScene::scene() {
  CCScene *scene = CCScene::create();
  TutorialScene *layer = TutorialScene::create();
  scene->addChild(layer);
  return scene;
}

bool TutorialScene::init() {
  if (!CCLayer::init()) {
    return false;
  }

  AbstractPanelScene::init();

  // Cursor
  cursor = CCSprite::createWithSpriteFrameName("cursor-01.png");
  cursor->setAnchorPoint(ccp(0, 0));
  batch->addChild(cursor);

  CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("tutorial.mp3", true);
  CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);

  cocos2d::CCSize size = cocos2d::CCDirector::sharedDirector()->getWinSize();

  textBox = cocos2d::CCLabelBMFont::create("textToType", "coopblack32.fnt", 200, kCCTextAlignmentLeft);
  textBox->setAnchorPoint(ccp(0, 1));
  textBox->setPosition(ccp(16, 414));
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

      CCSpriteFrame *frame = getBlockFrame(current, tick, panel.blocks[x][FuriousBlocksCoreDefaults::PANEL_HEIGHT] != nullptr, panel.blocks[x][FuriousBlocksCoreDefaults::PANEL_HEIGHT - 1] != nullptr);
      if (frame == nullptr) {
        grid[x][y]->setVisible(false);
        continue;
      }

      if (!panel.isGameOver()) {
        grid[x][y]->setPosition(ccp(xOffset + x * TILE_SIZE, yOffset + y * TILE_SIZE + panel.scrollingDelta * TILE_SIZE / FuriousBlocksCoreDefaults::BLOCK_LOGICALHEIGHT));
      }
      grid[x][y]->setDisplayFrame(frame);
      grid[x][y]->setVisible(true);
      if (y == 0) {
        grid[x][y]->setColor(ccc3(0x50, 0x50, 0x50));
      }

    }
  }

  cursor->setPosition(ccp(panel.cursor->x * TILE_SIZE, -6 + (panel.cursor->y - 1) * TILE_SIZE + panel.scrollingDelta * TILE_SIZE / FuriousBlocksCoreDefaults::BLOCK_LOGICALHEIGHT));

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
    new StarNumber(this, xOffset + combo->x * TILE_SIZE, yOffset + combo->y * TILE_SIZE, format("%d", combo->size()), ccORANGE);
  }
  if (combo->skillChainLevel > 1) {
    new StarNumber(this, xOffset + combo->x * TILE_SIZE, yOffset + (combo->y + 1) * TILE_SIZE, format("x%d", combo->skillChainLevel), ccc3(255, 128, 128));
  }
}

void TutorialScene::onGameOver() {
  // Initialize tweeners
  for (int y = 0; y < FuriousBlocksCoreDefaults::PANEL_HEIGHT + 1; y++) {
    for (int x = 0; x < FuriousBlocksCoreDefaults::PANEL_WIDTH; x++) {
      if (y > 0) {
        tweeners.insert(claw::tween::single_tweener(grid[x][y]->getPositionY(), random() % 350 + 500 + yOffset + y * TILE_SIZE, 2, boost::bind(&CCNode::setPositionY, grid[x][y], _1), claw::tween::easing_bounce::ease_in));
      }
    }
  }
}
