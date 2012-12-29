//
// Created by bquenin on 11/25/12.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include <algorithm>
#include <functional>
#include "LogoScene.h"
#include "TitleScene.h"
#include "Assets.h"
#include "easing_linear.hpp"

LogoScene::LogoScene() {
  for (int i = 0; i < num_blobs; i++) {
    blob_px[i] = rand() % width;
    blob_py[i] = rand() % height;
    blob_dx[i] = blob_dy[i] = 1;
  }
}

CCScene *LogoScene::scene() {
  CCScene *scene = CCScene::create();
  LogoScene *layer = LogoScene::create();
  scene->addChild(layer);
  return scene;
}

bool LogoScene::init() {
  if (!CCLayer::init()) {
    return false;
  }

  setTouchEnabled(true);

  CCSize texSize = CCSizeMake(LogoScene::width, LogoScene::height);
  size_t bytes = static_cast<size_t>(texSize.width * texSize.height * 4);
  void *textureData = malloc(bytes);
  memset(textureData, 0, bytes);

  texture = new CCTexture2DMutable();
  if (!texture->initWithData(textureData, kCCTexture2DPixelFormat_RGBA8888, texSize.width, texSize.height, texSize)) {
    CCLOG("Could not create texture");
    delete texture;
    texture = NULL;
  }

  texture->setAliasTexParameters();

//  claw::tween::single_tweener timerTweener(timer, 0, 5, claw::tween::easing_linear::ease_out);
//  timerTweener.on_finished(std::bind(&LogoScene::onTimerFinished, this));
//  tweeners.insert(timerTweener);

  CCSprite *canvas = CCSprite::createWithTexture(texture);
  canvas->setAnchorPoint(ccp(0, 0));
  canvas->setScaleX(Assets::designResolutionSize.width / LogoScene::width);
  canvas->setScaleY(Assets::designResolutionSize.height / LogoScene::height);
  addChild(canvas);

  CCLabelTTF *copyright = CCLabelTTF::create("PixodromE", "Joystix.ttf", 64);
  copyright->setPosition(ccp(Assets::designResolutionSize.width / 2, Assets::designResolutionSize.height / 2));
  copyright->setColor(ccc3(0, 0, 0));
  addChild(copyright);

  // Start scheduling
  schedule(schedule_selector(LogoScene::update));

  return true;
}

void LogoScene::update(float dt) {

  for (int i = 0; i < num_blobs; ++i) {
    blob_px[i] += blob_dx[i];
    blob_py[i] += blob_dy[i];

    // bounce across screen
    if (blob_px[i] < 0) {
      blob_dx[i] = 1;
    }
    if (blob_px[i] > width) {
      blob_dx[i] = -1;
    }
    if (blob_py[i] < 0) {
      blob_dy[i] = 1;
    }
    if (blob_py[i] > height) {
      blob_dy[i] = -1;
    }

    for (int x = 0; x < width; x++) {
      vx[i][x] = (blob_px[i] - x) * (blob_px[i] - x);
    }

    for (int y = 0; y < height; y++) {
      vy[i][y] = (blob_py[i] - y) * (blob_py[i] - y);
    }
  }

  int m = 1;
  int x = 0, y = 0;
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      m = 1;
      for (int i = 0; i < num_blobs; ++i) {
        // increase this number to make your blobs bigger
        m += 6000 / (vy[i][y] + vx[i][x] + 1);
      }
      texture->setPixelAt(CCPointMake(x, y), ccc4(std::min(m + y, 255), std::min(m + x, 255), std::min(m + x + y, 255), 255));
    }
  }

//  tweeners.update(dt);

  texture->apply();
}

void LogoScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {
  CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::create(Assets::transitionDuration, TitleScene::scene(), kOrientationUpOver));
}

void LogoScene::onTimerFinished(void) {
  CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::create(Assets::transitionDuration, TitleScene::scene(), kOrientationUpOver));
}