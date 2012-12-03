//
// Created by bquenin on 11/25/12.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "PanelMenuOverlay.h"

#include "TitleScene.h"
#include "SimpleAudioEngine.h"
#include "Assets.h"
#include "AppDelegate.h"

using namespace cocos2d;
using namespace CocosDenshion;

PanelMenuOverlay::PanelMenuOverlay() {
}

bool PanelMenuOverlay::init() {
  if (!CCLayer::init()) {
    return false;
  }

  initWithColor(ccc4(0, 0, 0, 80));

  /** Creates and return a button with a default background and title color. */
  CCScale9Sprite *skipBackgroundButton = CCScale9Sprite::createWithSpriteFrame(AppDelegate::assets.BUTTON);
  CCScale9Sprite *skipBackgroundHighlightedButton = CCScale9Sprite::createWithSpriteFrame(AppDelegate::assets.BUTTONHIGHLIGHTED);
  endGameButton = CCControlButton::create(CCLabelBMFont::create("Back to Title", "SkaterDudes.fnt"), skipBackgroundButton);
  endGameButton->setBackgroundSpriteForState(skipBackgroundHighlightedButton, CCControlStateHighlighted);
  endGameButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  endGameButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 + 40));
  endGameButton->setPreferredSize(CCSizeMake(endGameButton->getContentSize().width + 20, 60));
  endGameButton->addTargetWithActionForControlEvents(this, cccontrol_selector(PanelMenuOverlay::endGameAction), CCControlEventTouchUpInside);
  addChild(endGameButton);

  CCScale9Sprite *resumeBackgroundButton = CCScale9Sprite::createWithSpriteFrame(AppDelegate::assets.BUTTON);
  CCScale9Sprite *resumeBackgroundHighlightedButton = CCScale9Sprite::createWithSpriteFrame(AppDelegate::assets.BUTTONHIGHLIGHTED);
  resumeButton = CCControlButton::create(CCLabelBMFont::create("Continue", "SkaterDudes.fnt"), resumeBackgroundButton);
  resumeButton->setBackgroundSpriteForState(resumeBackgroundHighlightedButton, CCControlStateHighlighted);
  resumeButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  resumeButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 - 40));
  resumeButton->setPreferredSize(CCSizeMake(resumeButton->getContentSize().width + 20, 60));
  resumeButton->addTargetWithActionForControlEvents(this, cccontrol_selector(PanelMenuOverlay::resumeAction), CCControlEventTouchUpInside);
  addChild(resumeButton);

  CCLabelBMFont *on = CCLabelBMFont::create("On", "SkaterDudes.fnt");
  on->setScale(0.5);
  CCLabelBMFont *off = CCLabelBMFont::create("Off", "SkaterDudes.fnt");
  off->setScale(0.5);

  // Create the switch
  CCControlSwitch *musicSwitch = CCControlSwitch::create
      (
          CCSprite::create("switch-mask.png"),
          CCSprite::create("switch-on.png"),
          CCSprite::create("switch-off.png"),
          CCSprite::create("switch-thumb.png"),
          on, //CCLabelBMFont::create("On", "SkaterDudes.fnt"),
          off //CCLabelBMFont::create("Off", "SkaterDudes.fnt")
      );
  musicSwitch->setScale(1.5);
  musicSwitch->setPosition(ccp(Assets::designResolutionSize.width / 2 + 60, Assets::designResolutionSize.height / 2 - 120));
  musicSwitch->setOn(AppDelegate::musicOn);
  addChild(musicSwitch);

  musicSwitch->addTargetWithActionForControlEvents(this, cccontrol_selector(PanelMenuOverlay::valueChanged), CCControlEventValueChanged);

  setVisible(false);

  return true;
}

void PanelMenuOverlay::endGameAction(CCObject *sender) {
  setVisible(false);
  CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::create(Assets::transitionDuration, TitleScene::scene(), kOrientationUpOver));
}

void PanelMenuOverlay::resumeAction(CCObject *sender) {
  setVisible(false);
}

void PanelMenuOverlay::valueChanged(CCObject *sender, CCControlEvent controlEvent) {
  CCControlSwitch *pSwitch = (CCControlSwitch *) sender;
  AppDelegate::musicOn = pSwitch->isOn();
  if (AppDelegate::musicOn) {
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1);
  } else {
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
  }
}
