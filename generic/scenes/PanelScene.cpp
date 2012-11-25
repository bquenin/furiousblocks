#include "PanelScene.h"
#include "SimpleAudioEngine.h"
#include "easing_back.hpp"
#include "easing_bounce.hpp"
#include "easing_linear.hpp"
#include "easing_quad.hpp"
#include "TouchPlayer.h"
#include "SceneConstants.h"
#include "single_tweener.hpp"
#include "tweener_sequence.hpp"
#include "StarNumber.h"
#include <boost/bind.hpp>

using namespace CocosDenshion;

PanelScene::PanelScene()
: AbstractPanelScene()
, countdown(3) {
}

CCScene *PanelScene::scene() {
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

  AbstractPanelScene::init();

  setTouchEnabled(true);

  // Initialize the grid
  for (int y = 0; y < FuriousBlocksCoreDefaults::PANEL_HEIGHT + 1; y++) {
    for (int x = 0; x < FuriousBlocksCoreDefaults::PANEL_WIDTH; x++) {
      if (y > 0) {
        tweeners.insert(claw::tween::single_tweener(random() % 350 + SceneConstants::designResolutionSize.height + yOffset + y * TILE_SIZE, yOffset + y * TILE_SIZE, 2, boost::bind(&CCNode::setPositionY, grid[x][y], _1), claw::tween::easing_bounce::ease_out));
      }
    }
  }

  countdownLabel = CCLabelBMFont::create(format("%d", countdown).c_str(), "coopblack64.fnt");
  countdownLabel->setPosition(ccp(SceneConstants::designResolutionSize.width / 2, SceneConstants::designResolutionSize.height / 2));
  addChild(countdownLabel);

  CCLabelBMFont *scoreLabel = CCLabelBMFont::create("Score", "coopblack32.fnt");
  scoreLabel->setPosition(ccp(SceneConstants::designResolutionSize.width / 4, SceneConstants::designResolutionSize.height - 16 ));
  addChild(scoreLabel);

  score = CCLabelBMFont::create("Score", "coopblack32.fnt");
  score->setPosition(ccp(SceneConstants::designResolutionSize.width / 4, SceneConstants::designResolutionSize.height - 48));
  addChild(score);

  CCLabelBMFont *timeLabel = CCLabelBMFont::create("Time", "coopblack32.fnt");
  timeLabel->setPosition(ccp(SceneConstants::designResolutionSize.width * 3 / 4, SceneConstants::designResolutionSize.height - 16 ));
  addChild(timeLabel);

  minutes = CCLabelBMFont::create("Time", "coopblack32.fnt");
  minutes->setPosition(ccp(-64 + SceneConstants::designResolutionSize.width * 3 / 4, SceneConstants::designResolutionSize.height - 48));
  addChild(minutes);

  CCLabelBMFont *colon1 = CCLabelBMFont::create(":", "coopblack32.fnt");
  colon1->setPosition(ccp(-32 + SceneConstants::designResolutionSize.width * 3 / 4, SceneConstants::designResolutionSize.height - 48));
  addChild(colon1);

  seconds = CCLabelBMFont::create("Time", "coopblack32.fnt");
  seconds->setPosition(ccp(SceneConstants::designResolutionSize.width * 3 / 4, SceneConstants::designResolutionSize.height - 48));
  addChild(seconds);

  CCLabelBMFont *colon2 = CCLabelBMFont::create(":", "coopblack32.fnt");
  colon2->setPosition(ccp(32 + SceneConstants::designResolutionSize.width * 3 / 4, SceneConstants::designResolutionSize.height - 48));
  addChild(colon2);

  centisecs = CCLabelBMFont::create("Time", "coopblack32.fnt");
  centisecs->setPosition(ccp(64 + SceneConstants::designResolutionSize.width * 3 / 4, SceneConstants::designResolutionSize.height - 48));
  addChild(centisecs);

  youLose = CCSprite::createWithSpriteFrameName("lose.png");
  youLose->setPosition(ccp(SceneConstants::designResolutionSize.width / 2, SceneConstants::designResolutionSize.height / 2));
  youLose->setVisible(false);
  batch->addChild(youLose);

  CCScale9Sprite *backgroundButton = CCScale9Sprite::create("button.png");
  CCScale9Sprite *backgroundHighlightedButton = CCScale9Sprite::create("buttonHighlighted.png");
  menuButton = CCControlButton::create(CCLabelTTF::create("Menu", "SkaterDudes.ttf", 24), backgroundButton);
  menuButton->setBackgroundSpriteForState(backgroundHighlightedButton, CCControlStateHighlighted);
  menuButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  menuButton->setPosition(ccp(SceneConstants::designResolutionSize.width / 2, SceneConstants::designResolutionSize.height - 40));
  menuButton->setPreferredSize(CCSizeMake(menuButton->getContentSize().width + 10, 60));
  menuButton->addTargetWithActionForControlEvents(this, cccontrol_selector(PanelScene::menuAction), CCControlEventTouchUpInside);
  menuButton->setDefaultTouchPriority(-64);
  addChild(menuButton);

  claw::tween::single_tweener countDownTweener(0, 3, 1, boost::bind(&CCNode::setScale, countdownLabel, _1), claw::tween::easing_back::ease_out);
  countDownTweener.on_finished(boost::bind(&PanelScene::onBeginningTweenFinished, this));
  tweeners.insert(countDownTweener);

  // Game initialization
  core = new FuriousBlocksCore(0, this);

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

void PanelScene::onCombo(Combo *combo) {
  if (combo->size() > 3) {
    new StarNumber(this, xOffset + combo->x * TILE_SIZE, yOffset + combo->y * TILE_SIZE, format("%d", combo->size()), ccORANGE);
  }
  if (combo->skillChainLevel > 1) {
    new StarNumber(this, xOffset + combo->x * TILE_SIZE, yOffset + (combo->y + 1) * TILE_SIZE, format("x%d", combo->skillChainLevel), ccc3(255, 128, 128));
  }
}

void PanelScene::onGameOver() {
  youLose->setVisible(true);

  // Initialize the grid
  for (int y = 0; y < FuriousBlocksCoreDefaults::PANEL_HEIGHT + 1; y++) {
    for (int x = 0; x < FuriousBlocksCoreDefaults::PANEL_WIDTH; x++) {
      if (y > 0) {
        tweeners.insert(claw::tween::single_tweener(grid[x][y]->getPositionY(), random() % 350 + SceneConstants::designResolutionSize.height + yOffset + y * TILE_SIZE, 2, boost::bind(&CCNode::setPositionY, grid[x][y], _1), claw::tween::easing_bounce::ease_in));
      }
    }
  }

  claw::tween::single_tweener musicFadeOut(SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume(), 0, 2, boost::bind(&SimpleAudioEngine::setBackgroundMusicVolume, SimpleAudioEngine::sharedEngine(), _1), claw::tween::easing_linear::ease_in);
  musicFadeOut.on_finished([](){
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("gameover.mp3", true);
  });

  claw::tween::single_tweener musicFadeIn(0, SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume(), 2, boost::bind(&SimpleAudioEngine::setBackgroundMusicVolume, SimpleAudioEngine::sharedEngine(), _1), claw::tween::easing_linear::ease_in);

  claw::tween::tweener_group step2;
  step2.insert(musicFadeIn);
  step2.insert(claw::tween::single_tweener(SceneConstants::designResolutionSize.height + 100, SceneConstants::designResolutionSize.height / 2, 2, boost::bind(&CCNode::setPositionY, youLose, _1), claw::tween::easing_bounce::ease_out));

  claw::tween::tweener_sequence gameOverSequence;
  gameOverSequence.insert(musicFadeOut);
  gameOverSequence.insert(step2);
  tweeners.insert(gameOverSequence);
}

void PanelScene::onBeginningTweenFinished(void) {
  if (countdown > 1) {
    countdown--;
    countdownLabel->setCString(format("%d", countdown).c_str());
    claw::tween::single_tweener cdTweener(0, 3, 1, boost::bind(&CCNode::setScale, countdownLabel, _1), claw::tween::easing_back::ease_out);
    cdTweener.on_finished(boost::bind(&PanelScene::onBeginningTweenFinished, this));
    tweeners.insert(cdTweener);
  } else {
    gameRunning = true;
    removeChild(countdownLabel, true);
  }
}

void PanelScene::menuAction(CCObject *sender) {
  CCLOG("PanelScene::menuAction");
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
