//
// Created by bquenin on 11/25/12.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __LogoScene_H_
#define __LogoScene_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCTexture2DMutable.h"
#include "single_tweener.hpp"
#include "tweener_group.hpp"

using namespace cocos2d;
using namespace cocos2d::extension;

class LogoScene : public cocos2d::CCLayer {
private:
  static constexpr int num_blobs = 4;
  static constexpr int width = 16;
  static constexpr int height = 32;

  int blob_px[LogoScene::num_blobs];
  int blob_py[LogoScene::num_blobs];

  // movement vector for each blob
  int blob_dx[LogoScene::num_blobs];
  int blob_dy[LogoScene::num_blobs];

  int vx[LogoScene::num_blobs][LogoScene::width];
  int vy[LogoScene::num_blobs][LogoScene::height];

  CCTexture2DMutable* texture;

  double timer;
//  claw::tween::tweener_group tweeners;

public:
  // there's no 'id' in cpp, so we recommend to return the exactly class pointer
  static cocos2d::CCScene* scene();

  // Implement the "static node()" method manually
  CREATE_FUNC(LogoScene);

  LogoScene();
  bool init();
  void update(float dt);

  void ccTouchesBegan(CCSet* pTouches, CCEvent* pEvent);

  void onTimerFinished(void);
};


#endif //__LogoScene_H_
