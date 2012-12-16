//
// Created by tsug on 04/07/12.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "AdScene.h"
#include "Assets.h"
#include "AppDelegate.h"
#include "TitleScene.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#endif

#define ADTEXT "You ran out of games for today!\n\nHelp a small studio by buying the full version!"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene *AdScene::scene() {
  CCScene *scene = CCScene::create();
  scene->addChild(AdScene::create());
  return scene;
}

bool AdScene::init() {
  if (!CCLayer::init()) {
    return false;
  }

  // Background
  CCSprite *bg = CCSprite::createWithSpriteFrame(AppDelegate::assets.TITLE);
  bg->setAnchorPoint(ccp(0, 0));
  addChild(bg);

  CCLabelBMFont *textBox = CCLabelBMFont::create(ADTEXT, "coopblack32.fnt", 580, kCCTextAlignmentCenter);
  textBox->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2));
  addChild(textBox);

  CCControlButton *buyButton = CCControlButton::create(CCLabelTTF::create("Buy full version", "SkaterDudes.ttf", 42), CCScale9Sprite::create("button.png"));
  buyButton->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  buyButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  buyButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 8 + 160));
  buyButton->setPreferredSize(CCSizeMake(buyButton->getContentSize().width + 20, buyButton->getContentSize().height + 20));
  buyButton->addTargetWithActionForControlEvents(this, cccontrol_selector(AdScene::buyAction), CCControlEventTouchUpInside);
  addChild(buyButton);

  CCControlButton *backToTitleButton = CCControlButton::create(CCLabelTTF::create("Back to Title", "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
  backToTitleButton->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  backToTitleButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  backToTitleButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 8));
  backToTitleButton->setPreferredSize(CCSizeMake(backToTitleButton->getContentSize().width + 20, 60));
  backToTitleButton->addTargetWithActionForControlEvents(this, cccontrol_selector(AdScene::backToTitleAction), CCControlEventTouchUpInside);
  addChild(backToTitleButton);
  return true;
}

void AdScene::buyAction(CCObject *sender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  CCApplication::sharedApplication()->openURL("https://play.google.com/store/apps/details?id=me.pixodro.furiousblocks.commercial");
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;

    if(JniHelper::getStaticMethodInfo(minfo,
        "me/pixodro/FuriousBlocks",
        "openURL",
        "(Ljava/lang/String;)V"))
    {
        jstring StringArg1 = minfo.env->NewStringUTF("https://itunes.apple.com/us/app/furious-blocks/id586104129");
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, StringArg1);
        minfo.env->DeleteLocalRef(StringArg1);
        minfo.env->DeleteLocalRef(minfo.classID);
    }
#endif
}

void AdScene::backToTitleAction(CCObject *sender) {
  CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::create(Assets::transitionDuration, TitleScene::scene(), kOrientationUpOver));
}
