//
// Created by tsug on 04/07/12.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "CreditsScene.h"
#include "Assets.h"
#include "TitleScene.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#endif

using namespace cocos2d;
using namespace CocosDenshion;

CCScene *CreditsScene::scene() {
  CCScene *scene = CCScene::create();
  scene->addChild(CreditsScene::create());
  return scene;
}

bool CreditsScene::init() {
  if (!CCLayer::init()) {
    return false;
  }

  // Start music
  SimpleAudioEngine::sharedEngine()->playBackgroundMusic("voices.mp3", true);

  initWithColor(ccc4(0, 0, 0, 80));

  CCControlButton *codeButton = CCControlButton::create(CCLabelBMFont::create("Code: TsuG (tsug@pixodro.me)", "coopblack32.fnt", 580, kCCTextAlignmentCenter), CCScale9Sprite::create("button.png"));
  codeButton->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  codeButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  codeButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 + 60));
  codeButton->setPreferredSize(CCSizeMake(codeButton->getContentSize().width + 20, codeButton->getContentSize().height + 20));
  codeButton->addTargetWithActionForControlEvents(this, cccontrol_selector(CreditsScene::codeAction), CCControlEventTouchUpInside);
  addChild(codeButton);

  CCControlButton *graphicsButton = CCControlButton::create(CCLabelBMFont::create("Graphics: DoomCube (paul@doomcube.com)", "coopblack32.fnt", 580, kCCTextAlignmentCenter), CCScale9Sprite::create("button.png"));
  graphicsButton->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  graphicsButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  graphicsButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 - 60));
  graphicsButton->setPreferredSize(CCSizeMake(graphicsButton->getContentSize().width + 20, graphicsButton->getContentSize().height + 20));
  graphicsButton->addTargetWithActionForControlEvents(this, cccontrol_selector(CreditsScene::graphicsAction), CCControlEventTouchUpInside);
  addChild(graphicsButton);

  CCControlButton *musicButton = CCControlButton::create(CCLabelBMFont::create("Music: TsuG (tsug@pixodro.me)", "coopblack32.fnt", 580, kCCTextAlignmentCenter), CCScale9Sprite::create("button.png"));
  musicButton->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  musicButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  musicButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2 - 180));
  musicButton->setPreferredSize(CCSizeMake(musicButton->getContentSize().width + 20, musicButton->getContentSize().height + 20));
  musicButton->addTargetWithActionForControlEvents(this, cccontrol_selector(CreditsScene::musicAction), CCControlEventTouchUpInside);
  addChild(musicButton);

  CCControlButton *backToTitleButton = CCControlButton::create(CCLabelTTF::create("Back to Title", "SkaterDudes.ttf", 32), CCScale9Sprite::create("button.png"));
  backToTitleButton->setBackgroundSpriteForState(CCScale9Sprite::create("buttonHighlighted.png"), CCControlStateHighlighted);
  backToTitleButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
  backToTitleButton->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 8));
  backToTitleButton->setPreferredSize(CCSizeMake(backToTitleButton->getContentSize().width + 20, 60));
  backToTitleButton->addTargetWithActionForControlEvents(this, cccontrol_selector(CreditsScene::backToTitleAction), CCControlEventTouchUpInside);
  addChild(backToTitleButton);

  return true;
}

void CreditsScene::codeAction(CCObject *sender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  CCApplication::sharedApplication()->openURL("mailto:tsug@pixodro.me");
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;

    if(JniHelper::getStaticMethodInfo(minfo,
        "me/pixodro/FuriousBlocks",
        "openURL",
        "(Ljava/lang/String;)V"))
    {
        jstring StringArg1 = minfo.env->NewStringUTF("mailto:tsug@pixodro.me");
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, StringArg1);
        minfo.env->DeleteLocalRef(StringArg1);
        minfo.env->DeleteLocalRef(minfo.classID);
    }
#endif
}

void CreditsScene::graphicsAction(CCObject *sender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  CCApplication::sharedApplication()->openURL("mailto:paul@doomcube.com");
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;

    if(JniHelper::getStaticMethodInfo(minfo,
        "me/pixodro/FuriousBlocks",
        "openURL",
        "(Ljava/lang/String;)V"))
    {
        jstring StringArg1 = minfo.env->NewStringUTF("mailto:paul@doomcube.com");
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, StringArg1);
        minfo.env->DeleteLocalRef(StringArg1);
        minfo.env->DeleteLocalRef(minfo.classID);
    }
#endif
}

void CreditsScene::musicAction(CCObject *sender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  CCApplication::sharedApplication()->openURL("mailto:tsug@pixodro.me");
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;

    if(JniHelper::getStaticMethodInfo(minfo,
        "me/pixodro/FuriousBlocks",
        "openURL",
        "(Ljava/lang/String;)V"))
    {
        jstring StringArg1 = minfo.env->NewStringUTF("mailto:tsug@pixodro.me");
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, StringArg1);
        minfo.env->DeleteLocalRef(StringArg1);
        minfo.env->DeleteLocalRef(minfo.classID);
    }
#endif
}

void CreditsScene::backToTitleAction(CCObject *sender) {
  CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::create(Assets::transitionDuration, TitleScene::scene(), kOrientationUpOver));
}

