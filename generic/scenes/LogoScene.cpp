//
// Created by bquenin on 11/25/12.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include <algorithm>
#include "LogoScene.h"
#include "SceneConstants.h"
#include "TitleScene.h"

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
  memset(textureData, INT32_MAX, bytes);

  texture = new CCTexture2DMutable();
  if (!texture->initWithData(textureData, kCCTexture2DPixelFormat_RGBA8888, texSize.width, texSize.height, texSize)) {
    CCLOG("Could not create texture");
    delete texture;
    texture = NULL;
  }

  texture->setAliasTexParameters();

  CCSprite *sprite = CCSprite::createWithTexture(texture);
  sprite->setAnchorPoint(ccp(0, 0));
  sprite->setScaleX(SceneConstants::designResolutionSize.width / LogoScene::width);
  sprite->setScaleY(SceneConstants::designResolutionSize.height / LogoScene::height);
  addChild(sprite);

  texture->autorelease();

  CCLabelTTF *copyright = CCLabelTTF::create("PixodromE", "Joystix.ttf", 32);
  copyright->setPosition(ccp(SceneConstants::designResolutionSize.width / 2, SceneConstants::designResolutionSize.height / 2));
  copyright->setColor(ccc3(0, 0, 0));
  copyright->setScale(2);
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
      //            CCLOG("color = %d:%d:%d", m + y, m + x, m + x + y);
      int r = std::min(m + y, 255);
      int g = std::min(m + x, 255);
      int b = std::min(m + x + y, 255);

      texture->setPixelAt(CCPointMake(x, y), ccc4(r, g, b, 255));
    }
  }
  texture->apply();
}

void LogoScene::registerWithTouchDispatcher() {
  cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool LogoScene::ccTouchBegan(CCTouch *touch, CCEvent *event) {
  CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::create(SceneConstants::transitionDuration, TitleScene::scene(), kOrientationUpOver));
  return true;
}

void LogoScene::ccTouchEnded(CCTouch *touch, CCEvent *event) {
}

void LogoScene::ccTouchMoved(CCTouch *touch, CCEvent *event) {
}

