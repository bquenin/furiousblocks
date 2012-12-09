//
// Created by tsug on 04/07/12.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __AdScene_H_
#define __AdScene_H_

#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class AdScene : public cocos2d::CCLayer {

public:
  // there's no 'id' in cpp, so we recommend to return the exactly class pointer
  static cocos2d::CCScene *scene();

  // Implement the "static node()" method manually
  CREATE_FUNC(AdScene);

  bool init();
  void backToTitleAction(CCObject *sender);
  void buyAction(CCObject *sender);
};


#endif //__AdScene_H_
