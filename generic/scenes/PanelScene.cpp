//
// Created by bquenin on 11/12/12.
//
// To change the template use AppCode | Preferences | File Templates.
//

#include <functional>
#include "PanelScene.h"
#include "SimpleAudioEngine.h"
#include "easing_back.hpp"
#include "easing_bounce.hpp"
#include "easing_linear.hpp"
#include "easing_quad.hpp"
#include "TouchPlayer.h"
#include "single_tweener.hpp"
#include "tweener_sequence.hpp"
#include "StarNumber.h"
#include "Assets.h"
#include "AppDelegate.h"
#include "Social.h"

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

CCScene *PanelScene::scene() {
#ifdef FREEMIUM
  // Check games left
  int32_t gamesLeft = AppDelegate::getGamesLeft();

  if (gamesLeft <= 0 || gamesLeft > 5) {
    CCScene *scene = CCScene::create();
    scene->addChild(AdScene::create());
    return scene;
  }

  // Decrease games left
  AppDelegate::setGamesLeft(gamesLeft - 1);
#endif

  CCScene *scene = CCScene::create();
  PanelScene *layer = PanelScene::create();
  scene->addChild(layer);
  PanelMenuOverlay *menuOverlay = PanelMenuOverlay::create();
  scene->addChild(menuOverlay);
  layer->setOverlay(menuOverlay);
  return scene;
}

bool PanelScene::init() {
  if (!CCLayer::init()) {
    return false;
  }

  // Start music
  SimpleAudioEngine::sharedEngine()->playBackgroundMusic("harmonic.mp3", true);

  AbstractPanelScene::init();

  setTouchEnabled(true);

  // Initialize the grid
  for (int y = 0; y < FuriousBlocksCoreDefaults::PANEL_HEIGHT + 1; y++) {
    for (int x = 0; x < FuriousBlocksCoreDefaults::PANEL_WIDTH; x++) {
      if (y > 0) {
        tweeners.insert(claw::tween::single_tweener(random() % 350 + Assets::designResolutionSize.height + yOffset + y * Assets::TILE_SIZE, yOffset + y * Assets::TILE_SIZE, 2, std::bind(&CCNode::setPositionY, grid[x][y], _1), claw::tween::easing_bounce::ease_out));
      }
    }
  }

  countdownLabel = CCLabelBMFont::create(Assets::format("%d", countdown).c_str(), "coopblack64.fnt");
  countdownLabel->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2));
  addChild(countdownLabel);

  CCLabelBMFont *scoreLabel = CCLabelBMFont::create("Score", "coopblack32.fnt");
  scoreLabel->setPosition(ccp(Assets::designResolutionSize.width / 4, Assets::designResolutionSize.height - 16 ));
  addChild(scoreLabel);

  score = CCLabelBMFont::create("Score", "coopblack32.fnt");
  score->setPosition(ccp(Assets::designResolutionSize.width / 4, Assets::designResolutionSize.height - 48));
  addChild(score);

  CCLabelBMFont *timeLabel = CCLabelBMFont::create("Time", "coopblack32.fnt");
  timeLabel->setPosition(ccp(Assets::designResolutionSize.width * 3 / 4, Assets::designResolutionSize.height - 16 ));
  addChild(timeLabel);

  minutes = CCLabelBMFont::create("Time", "coopblack32.fnt");
  minutes->setPosition(ccp(-64 + Assets::designResolutionSize.width * 3 / 4, Assets::designResolutionSize.height - 48));
  addChild(minutes);

  CCLabelBMFont *colon1 = CCLabelBMFont::create(":", "coopblack32.fnt");
  colon1->setPosition(ccp(-32 + Assets::designResolutionSize.width * 3 / 4, Assets::designResolutionSize.height - 48));
  addChild(colon1);

  seconds = CCLabelBMFont::create("Time", "coopblack32.fnt");
  seconds->setPosition(ccp(Assets::designResolutionSize.width * 3 / 4, Assets::designResolutionSize.height - 48));
  addChild(seconds);

  CCLabelBMFont *colon2 = CCLabelBMFont::create(":", "coopblack32.fnt");
  colon2->setPosition(ccp(32 + Assets::designResolutionSize.width * 3 / 4, Assets::designResolutionSize.height - 48));
  addChild(colon2);

  centisecs = CCLabelBMFont::create("Time", "coopblack32.fnt");
  centisecs->setPosition(ccp(64 + Assets::designResolutionSize.width * 3 / 4, Assets::designResolutionSize.height - 48));
  addChild(centisecs);

  youLose = CCSprite::createWithSpriteFrameName("lose.png");
  youLose->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2));
  youLose->setVisible(false);
  batch->addChild(youLose);

  CCScale9Sprite *backgroundButton = CCScale9Sprite::create("button.png");
  CCScale9Sprite *backgroundHighlightedButton = CCScale9Sprite::create("buttonHighlighted.png");
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
  core = new FuriousBlocksCore(rand(), this);

  // Player initialization
  player = new TouchPlayer();
  core->addPlayer(player);

  // Start scheduling
  schedule(schedule_selector(PanelScene::update));

  return true;
}

void PanelScene::update(float dt) {
  // Situation rendering
  Panel const &panel = *core->playerToPanel[player];

  // Blocks
  for (int y = 0; y < FuriousBlocksCoreDefaults::PANEL_HEIGHT + 1; y++) {
    for (int x = 0; x < FuriousBlocksCoreDefaults::PANEL_WIDTH; x++) {
      fb::Block *current = panel.blocks[x][y];
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

  // Tweeners update
  tweeners.update(dt);

  // Score
  score->setString(Assets::format("%d", panel.score).c_str());
  panelMenuOverlay->score->setString(Assets::format("%d", panel.score).c_str());

  // Time
  minutes->setString(Assets::format("%02d", static_cast<int32_t>(stateTime / 60)).c_str());
  seconds->setString(Assets::format("%02d", static_cast<int32_t>(stateTime) % 60).c_str());
  centisecs->setString(Assets::format("%02d", static_cast<int32_t>(stateTime * 100) % 100).c_str());

  if (!gameRunning || panel.isGameOver()) {
    return;
  }

  // State time update
  stateTime += dt;

  // Core tick
  core->onTick(tick++);
}

void PanelScene::onCombo(Combo *combo) {
  if (combo->size() > 3) {
    new StarNumber(this, xOffset + combo->x * Assets::TILE_SIZE, yOffset + combo->y * Assets::TILE_SIZE, Assets::format("%d", combo->size()), ccORANGE);
  }
  if (combo->skillChainLevel > 1) {
    new StarNumber(this, xOffset + combo->x * Assets::TILE_SIZE, yOffset + (combo->y + 1) * Assets::TILE_SIZE, Assets::format("x%d", combo->skillChainLevel), ccc3(255, 128, 128));
  }
}

void PanelScene::onGameOver() {
  panelMenuOverlay->continueButton->setVisible(false);
  youLose->setVisible(true);

  // Store the score
  if (AppDelegate::isLoggedIn()) {
    Social::registerPlayer();
    Social::submitScore(core->playerToPanel[player]->score);
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
    countdownLabel->setCString(Assets::format("%d", countdown).c_str());
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

void PanelScene::menuAction(CCObject *sender) {
  panelMenuOverlay->setVisible(true);
}

void PanelScene::setOverlay(PanelMenuOverlay *panelMenuOverlay) {
  this->panelMenuOverlay = panelMenuOverlay;
}

void PanelScene::registerWithTouchDispatcher() {
  cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -32, true);
}

bool PanelScene::ccTouchBegan(CCTouch *touch, CCEvent *event) {
  if (panelMenuOverlay->isVisible()) {
    return false;
  }
  return true;
}

void PanelScene::ccTouchEnded(CCTouch *touch, CCEvent *event) {
}
