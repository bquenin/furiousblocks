//
// Created by bquenin on 11/2/12.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "TutorialScene.h"
#include "SimpleAudioEngine.h"
#include "StarNumber.h"
#include "easing_back.hpp"
#include "easing_bounce.hpp"
#include "easing_linear.hpp"
#include "easing_quad.hpp"
#include "tweener_sequence.hpp"
#include "TouchPlayer.h"
#include <boost/bind.hpp>

using namespace CocosDenshion;

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
  //  cursor = CCSprite::createWithSpriteFrameName("cursor-01.png");
  //  cursor->setAnchorPoint(ccp(0, 0));
  //  batch->addChild(cursor);

  SimpleAudioEngine::sharedEngine()->playBackgroundMusic("tutorial.mp3", true);
  SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);

  // Game initialization
  core = new FuriousBlocksCore(0, this);

  // Player initialization
  player = new TouchPlayer();
  core->addPlayer(player);

  // Start scheduling
  schedule(schedule_selector(TutorialScene::update));

  return true;
}

void TutorialScene::update(float dt) {
  // Situation rendering
  Panel const &panel = *core->playerToPanel[player];

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

  // Tweeners update
  tweeners.update(dt);

  // Score
  score->setString(format("%d", panel.score).c_str());

  // Time
  minutes->setString(format("%02d", static_cast<int32_t>(stateTime / 60)).c_str());
  seconds->setString(format("%02d", static_cast<int32_t>(stateTime) % 60).c_str());
  centisecs->setString(format("%02d", static_cast<int32_t>(stateTime * 100) % 100).c_str());

  if (!gameRunning || panel.isGameOver()) {
    return;
  }

  // State time update
  stateTime += dt;

  // Core tick
  core->onTick(tick++);
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
  CCSize size = CCDirector::sharedDirector()->getWinSize();
  youLose->setVisible(true);

  // Initialize the grid
  for (int y = 0; y < FuriousBlocksCoreDefaults::PANEL_HEIGHT + 1; y++) {
    for (int x = 0; x < FuriousBlocksCoreDefaults::PANEL_WIDTH; x++) {
      if (y > 0) {
        tweeners.insert(claw::tween::single_tweener(grid[x][y]->getPositionY(), random() % 350 + 500 + yOffset + y * TILE_SIZE, 2, boost::bind(&CCNode::setPositionY, grid[x][y], _1), claw::tween::easing_bounce::ease_in));
      }
    }
  }

  claw::tween::single_tweener musicFadeOut(1.0, 0, 2, boost::bind(&SimpleAudioEngine::setBackgroundMusicVolume, SimpleAudioEngine::sharedEngine(), _1), claw::tween::easing_linear::ease_in);
  musicFadeOut.on_finished([](){
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("gameover.mp3", true);
  });

  claw::tween::single_tweener musicFadeIn(0, 1.0, 2, boost::bind(&SimpleAudioEngine::setBackgroundMusicVolume, SimpleAudioEngine::sharedEngine(), _1), claw::tween::easing_linear::ease_in);

  claw::tween::tweener_group step2;
  step2.insert(musicFadeIn);
  step2.insert(claw::tween::single_tweener(500, size.height / 2, 2, boost::bind(&CCNode::setPositionY, youLose, _1), claw::tween::easing_bounce::ease_out));

  claw::tween::tweener_sequence gameOverSequence;
  gameOverSequence.insert(musicFadeOut);
  gameOverSequence.insert(step2);
  tweeners.insert(gameOverSequence);
}