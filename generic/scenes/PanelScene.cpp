//
// Created by bquenin on 11/12/12.
//

#include <functional>
#include "PanelScene.h"
#include "SimpleAudioEngine.h"
#include "easing_back.hpp"
#include "easing_bounce.hpp"
#include "easing_linear.hpp"
#include "easing_quad.hpp"
#include "single_tweener.hpp"
#include "tweener_sequence.hpp"
#include "StarNumber.h"
#include "Assets.h"
#include "AppDelegate.h"
#include "Social.h"

#ifdef DEBUG

#include "ComputerPlayer.h"

#else
#include "TouchPlayer.h"
#endif

#ifdef FREEMIUM
#include "AdScene.h"
#endif

using namespace CocosDenshion;
using namespace std::placeholders;

PanelScene::PanelScene()
: AbstractPanelScene()
, countdown(3)
, gameOver(false) {
}

PanelScene::~PanelScene() {
  cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

CCScene* PanelScene::scene() {
#ifdef FREEMIUM
  // Check games left
  int32_t gamesLeft = Social::gamesLeft();

  if (gamesLeft <= 0) {
    CCScene *scene = CCScene::create();
    scene->addChild(AdScene::create());
    return scene;
  }

  // Decrease games left
  Social::beginGame();
#endif

  CCScene* scene = CCScene::create();
  PanelScene* layer = PanelScene::create();
  scene->addChild(layer);
  PanelMenuOverlay* menuOverlay = PanelMenuOverlay::create();
  scene->addChild(menuOverlay);
  layer->setOverlay(menuOverlay);
  return scene;
}

bool PanelScene::init() {
  if (!CCLayer::init()) {
    return false;
  }

  AbstractPanelScene::init();

  setTouchEnabled(true);

#if DEBUG
  // Cursor
  cursor = CCSprite::createWithSpriteFrame(AppDelegate::assets.CURSOR_01);
  cursor->setAnchorPoint(ccp(0, 0));
  batch->addChild(cursor);

  // Cursor
  aiTarget = CCSprite::createWithSpriteFrame(AppDelegate::assets.SPINNER);
  addChild(aiTarget);
#endif

  // Initialize the grid
  for (int y = 0; y < FuriousBlocksCoreDefaults::PANEL_HEIGHT + 1; y++) {
    for (int x = 0; x < FuriousBlocksCoreDefaults::PANEL_WIDTH; x++) {
      if (y > 0) {
        tweeners.insert(claw::tween::single_tweener(random() % 350 + Assets::designResolutionSize.height + yOffset + y * Assets::TILE_SIZE, yOffset + y * Assets::TILE_SIZE, 2, std::bind(&CCNode::setPositionY, grid[x][y], _1), claw::tween::easing_bounce::ease_out));
      }
    }
  }

  countdownLabel = CCLabelBMFont::create(CCString::createWithFormat("%d", countdown)->getCString(), "coopblack64.fnt");
  countdownLabel->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2));
  addChild(countdownLabel);

  CCLabelBMFont* scoreLabel = CCLabelBMFont::create("Score", "coopblack32.fnt");
  scoreLabel->setPosition(ccp(16 + Assets::designResolutionSize.width * 3 / 4, Assets::designResolutionSize.height - 16 ));
  addChild(scoreLabel);

  score = CCLabelBMFont::create("Score", "coopblack32.fnt");
  score->setPosition(ccp(16 + Assets::designResolutionSize.width * 3 / 4, Assets::designResolutionSize.height - 48));
  addChild(score);

  CCLabelBMFont* timeLabel = CCLabelBMFont::create("Time", "coopblack32.fnt");
  timeLabel->setPosition(ccp(16 + Assets::designResolutionSize.width / 4, Assets::designResolutionSize.height - 16 ));
  addChild(timeLabel);

  minutes = CCLabelBMFont::create("Time", "coopblack32.fnt");
  minutes->setPosition(ccp(-64 + 16 + Assets::designResolutionSize.width / 4, Assets::designResolutionSize.height - 48));
  addChild(minutes);

  CCLabelBMFont* colon1 = CCLabelBMFont::create(":", "coopblack32.fnt");
  colon1->setPosition(ccp(-32 + 16 + Assets::designResolutionSize.width / 4, Assets::designResolutionSize.height - 48));
  addChild(colon1);

  seconds = CCLabelBMFont::create("Time", "coopblack32.fnt");
  seconds->setPosition(ccp(16 + Assets::designResolutionSize.width / 4, Assets::designResolutionSize.height - 48));
  addChild(seconds);

  CCLabelBMFont* colon2 = CCLabelBMFont::create(":", "coopblack32.fnt");
  colon2->setPosition(ccp(32 + 16 + Assets::designResolutionSize.width / 4, Assets::designResolutionSize.height - 48));
  addChild(colon2);

  centisecs = CCLabelBMFont::create("Time", "coopblack32.fnt");
  centisecs->setPosition(ccp(64 + 16 + Assets::designResolutionSize.width / 4, Assets::designResolutionSize.height - 48));
  addChild(centisecs);

  CCLabelBMFont* levelLabel = CCLabelBMFont::create("Lvl", "coopblack32.fnt");
  levelLabel ->setPosition(ccp(48, Assets::designResolutionSize.height - 16));
  addChild(levelLabel);

  level = CCLabelBMFont::create("Lvl.", "coopblack32.fnt");
  level->setPosition(ccp(48, Assets::designResolutionSize.height - 48));
  addChild(level);

  youLose = CCSprite::createWithSpriteFrameName("lose.png");
  youLose->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2));
  youLose->setVisible(false);
  batch->addChild(youLose);

  CCScale9Sprite* backgroundButton = CCScale9Sprite::create("button.png");
  CCScale9Sprite* backgroundHighlightedButton = CCScale9Sprite::create("buttonHighlighted.png");
  menuButton = CCControlButton::create(CCLabelTTF::create("Menu", "SkaterDudes.ttf", 24), backgroundButton);
  menuButton->setBackgroundSpriteForState(backgroundHighlightedButton, CCControlStateHighlighted);
  menuButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  menuButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height - 40));
  menuButton->setPreferredSize(CCSizeMake(menuButton->getContentSize().width + 10, 60));
  menuButton->addTargetWithActionForControlEvents(this, cccontrol_selector(PanelScene::menuAction), CCControlEventTouchUpInside);
  menuButton->setDefaultTouchPriority(-64);
  addChild(menuButton);

  claw::tween::single_tweener countDownTweener(0, 3, 1, std::bind(&CCNode::setScale, countdownLabel, _1), claw::tween::easing_back::ease_out);
  countDownTweener.on_finished(std::bind(&PanelScene::onBeginningTweenFinished, this));
  tweeners.insert(countDownTweener);

  // Game initialization
  core = new FuriousBlocksCore(rand(), *this);

  // Player initialization
#if DEBUG
  player = new ComputerPlayer();
#else
  player = new TouchPlayer();
#endif
  core->addPlayer(player);

  // Start scheduling
  schedule(schedule_selector(PanelScene::update));

  return true;
}

void PanelScene::update(float dt) {
  // State time update
  stateTime += dt;

  // Tweeners update
  tweeners.update(dt);

  // Core update
  Panel const &panel = *core->playerToPanel[player];

  // Core tick
  if (gameRunning && !panel.gameOver) {
    core->onTick(tick++);
  }

  // Blocks
  for (int y = 0; y < FuriousBlocksCoreDefaults::PANEL_HEIGHT + 1; y++) {
    for (int x = 0; x < FuriousBlocksCoreDefaults::PANEL_WIDTH; x++) {
      auto& current = panel.blocks[x][y];
      if (!current) {
#if DEBUG
        debug[x][y]->setVisible(false);
#endif
        grid[x][y]->setVisible(false);
        continue;
      }

#if DEBUG
      switch (current->state) {
        case BlockState::BLINKING:
          debug[x][y]->setString("B");
          break;
        case BlockState::DONE_BLINKING:
          debug[x][y]->setString("DB");
          break;
        case BlockState::EXPLODING:
          debug[x][y]->setString("E");
          break;
        case BlockState::DONE_EXPLODING:
          debug[x][y]->setString("DE");
          break;
        case BlockState::IDLE:
          debug[x][y]->setString("I");
          break;
        case BlockState::REVEALING:
          debug[x][y]->setString("R");
          break;
        case BlockState::DONE_REVEALING:
          debug[x][y]->setString("DR");
          break;
        case BlockState::SWITCHING_BACK:
          debug[x][y]->setString("DSB");
          break;
        case BlockState::SWITCHING_FORTH:
          debug[x][y]->setString("DSF");
          break;
        case BlockState::DONE_SWITCHING_FORTH:
          debug[x][y]->setString("DS");
          break;
        case BlockState::TO_DELETE:
          debug[x][y]->setString("TD");
          break;
        case BlockState::HOVERING:
          debug[x][y]->setString("H");
          break;
        case BlockState::DONE_HOVERING:
          debug[x][y]->setString("DH");
          break;
        case BlockState::FALLING:
          debug[x][y]->setString("F");
          break;
        case BlockState::AIRBOUNCING:
          debug[x][y]->setString("AB");
          break;
        case BlockState::DONE_AIRBOUNCING:
          debug[x][y]->setString("DAB");
          break;
      }
#endif

      CCSpriteFrame* frame = AppDelegate::assets.getBlockFrame(current, tick, panel.blocks[x][FuriousBlocksCoreDefaults::PANEL_HEIGHT] != nullptr, panel.blocks[x][FuriousBlocksCoreDefaults::PANEL_HEIGHT - 1] != nullptr);
      if (frame == nullptr) {
        grid[x][y]->setVisible(false);
        continue;
      }

      if (!panel.gameOver) {
        grid[x][y]->setPosition(ccp(xOffset + x * Assets::TILE_SIZE, yOffset + y * Assets::TILE_SIZE + panel.scrollingDelta * Assets::TILE_SIZE / FuriousBlocksCoreDefaults::BLOCK_LOGICALHEIGHT));

#if DEBUG
        debug[x][y]->setPosition(ccp(xOffset + x * Assets::TILE_SIZE, yOffset + y * Assets::TILE_SIZE + panel.scrollingDelta * Assets::TILE_SIZE / FuriousBlocksCoreDefaults::BLOCK_LOGICALHEIGHT));
#endif
      }
      grid[x][y]->setDisplayFrame(frame);
      grid[x][y]->setVisible(true);
#if DEBUG
      debug[x][y]->setVisible(true);
#endif
      if (y == 0) {
        grid[x][y]->setColor(ccc3(0x50, 0x50, 0x50));
      }
    }
  }

#if DEBUG
  cursor->setPosition(ccp(panel.cursor.x * Assets::TILE_SIZE, -16 + (panel.cursor.y - 1) * Assets::TILE_SIZE + panel.scrollingDelta * Assets::TILE_SIZE / FuriousBlocksCoreDefaults::BLOCK_LOGICALHEIGHT));
  auto&& target = static_cast<ComputerPlayer*>(player)->cursorMoving;
  if (static_cast<ComputerPlayer*>(player)->cursorMoving) {
    auto&& target = static_cast<ComputerPlayer*>(player)->targetPosition;
    aiTarget->setVisible(true);
    aiTarget->setPosition(ccp(target.x * Assets::TILE_SIZE, -16 + target.y * Assets::TILE_SIZE + panel.scrollingDelta * Assets::TILE_SIZE / FuriousBlocksCoreDefaults::BLOCK_LOGICALHEIGHT));
  } else {
    aiTarget->setVisible(false);
  }
#endif

  // Level
  level->setString(CCString::createWithFormat("%d", panel.level)->getCString());

  // Score
  std::stringstream scoreText;
  scoreText << panel.score;
  score->setString(scoreText.str().c_str());
  panelMenuOverlay->score->setString(scoreText.str().c_str());

  // Time
  minutes->setString(CCString::createWithFormat("%02d", static_cast<int32_t>(stateTime / 60))->getCString());
  seconds->setString(CCString::createWithFormat("%02d", static_cast<int32_t>(stateTime) % 60)->getCString());
  centisecs->setString(CCString::createWithFormat("%02d", static_cast<int32_t>(stateTime * 100) % 100)->getCString());
}

void PanelScene::onCombo(Combo* combo) {
  if (combo->size() > 3) {
    new StarNumber(this, xOffset + combo->x * Assets::TILE_SIZE, yOffset + combo->y * Assets::TILE_SIZE, CCString::createWithFormat("%d", combo->size())->getCString(), ccORANGE);
  }
  if (combo->skillChainLevel > 1) {
    new StarNumber(this, xOffset + combo->x * Assets::TILE_SIZE, yOffset + (combo->y + 1) * Assets::TILE_SIZE, CCString::createWithFormat("x%d", combo->skillChainLevel)->getCString(), ccc3(255, 128, 128));
  }
}

void PanelScene::onGameOver() {
  panelMenuOverlay->continueButton->setVisible(false);
  youLose->setVisible(true);

  // Store the score
  if (AppDelegate::isLoggedIn()) {
    Social::submitScore(core->playerToPanel[player]->score, core->playerToPanel[player]->level, static_cast<uint32_t>(stateTime * 1000));
  }

  // Initialize the grid
  for (int y = 0; y < FuriousBlocksCoreDefaults::PANEL_HEIGHT + 1; y++) {
    for (int x = 0; x < FuriousBlocksCoreDefaults::PANEL_WIDTH; x++) {
      if (y > 0) {
        tweeners.insert(claw::tween::single_tweener(grid[x][y]->getPositionY(), random() % 350 + Assets::designResolutionSize.height + yOffset + y * Assets::TILE_SIZE, 2, std::bind(&CCNode::setPositionY, grid[x][y], _1), claw::tween::easing_bounce::ease_in));
      }
    }
  }

  claw::tween::single_tweener musicFadeOut(SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume(), 0, 2, std::bind(&SimpleAudioEngine::setBackgroundMusicVolume, SimpleAudioEngine::sharedEngine(), _1), claw::tween::easing_linear::ease_in);
  musicFadeOut.on_finished([](){
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("gameover.mp3", true);
  });

  claw::tween::single_tweener musicFadeIn(0, SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume(), 2, std::bind(&SimpleAudioEngine::setBackgroundMusicVolume, SimpleAudioEngine::sharedEngine(), _1), claw::tween::easing_linear::ease_in);

  claw::tween::tweener_group musicFadeInAndDisplayMenu;
  musicFadeInAndDisplayMenu.insert(musicFadeIn);
  claw::tween::single_tweener lastStep(Assets::designResolutionSize.height + 100, Assets::designResolutionSize.height / 2, 2, std::bind(&CCNode::setPositionY, youLose, _1), claw::tween::easing_bounce::ease_out);
  lastStep.on_finished(std::bind(&PanelScene::onLastStepFinished, this));
  musicFadeInAndDisplayMenu.insert(lastStep);

  claw::tween::tweener_sequence gameOverSequence;
  gameOverSequence.insert(musicFadeOut);
  gameOverSequence.insert(musicFadeInAndDisplayMenu);
  tweeners.insert(gameOverSequence);
}

void PanelScene::onBeginningTweenFinished(void) {
  if (countdown > 1) {
    countdown--;
    countdownLabel->setCString(CCString::createWithFormat("%d", countdown)->getCString());
    claw::tween::single_tweener cdTweener(0, 3, 1, std::bind(&CCNode::setScale, countdownLabel, _1), claw::tween::easing_back::ease_out);
    cdTweener.on_finished(std::bind(&PanelScene::onBeginningTweenFinished, this));
    tweeners.insert(cdTweener);
  } else {
    gameRunning = true;
    removeChild(countdownLabel, true);
  }
}

void PanelScene::onLastStepFinished() {
  panelMenuOverlay->setVisible(true);
}

void PanelScene::menuAction(CCObject* sender) {
  panelMenuOverlay->setVisible(true);
}

void PanelScene::setOverlay(PanelMenuOverlay* panelMenuOverlay) {
  this->panelMenuOverlay = panelMenuOverlay;
}

void PanelScene::registerWithTouchDispatcher() {
  cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -32, true);
}

bool PanelScene::ccTouchBegan(CCTouch* touch, CCEvent* event) {
  if (panelMenuOverlay->isVisible()) {
    return false;
  }
  return true;
}

void PanelScene::ccTouchEnded(CCTouch* touch, CCEvent* event) {
}
