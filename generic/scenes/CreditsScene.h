//
// Created by tsug on 04/07/12.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __CreditsScene_H_
#define __CreditsScene_H_

#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class CreditsScene : public cocos2d::CCLayerColor {

public:
  // there's no 'id' in cpp, so we recommend to return the exactly class pointer
  static cocos2d::CCScene *scene();

  // Implement the "static node()" method manually
  CREATE_FUNC(CreditsScene);

  bool init();
  void codeAction(CCObject *sender);
  void musicAction(CCObject *sender);
  void graphicsAction(CCObject *sender);
  void backToTitleAction(CCObject *sender);
};


#endif //__CreditsScene_H_
