//
// Created by tsug on 04/07/12.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __TitleScene_H_
#define __TitleScene_H_

#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class TitleScene : public cocos2d::CCLayer {
private:
  CCControlButton *playButton;
  CCScale9Sprite *playBackgroundButton;
  CCScale9Sprite *playBackgroundHighlightedButton;

  CCControlButton *howToPlaylButton;
  CCScale9Sprite *howToPlayBackgroundButton;
  CCScale9Sprite *howToPlayBackgroundHighlightedButton;

  CCSprite *bg;

  CCLabelTTF *copyright;

public:
  bool init();
  void playAction(CCObject *sender);
  void howToPlayAction(CCObject *sender);

  // there's no 'id' in cpp, so we recommend to return the exactly class pointer
  static cocos2d::CCScene *scene();

  // Implement the "static node()" method manually
  CREATE_FUNC(TitleScene);

};


#endif //__TitleScene_H_
