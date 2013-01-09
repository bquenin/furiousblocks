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
  // Ugly but convenient
  CCControlButton *logIn;
  CCControlButton *logOut;
  CCControlButton *musicSwitchOn;
  CCControlButton *musicSwitchOff;

  static const std::string FACEBOOK_URI;

public:

  // there's no 'id' in cpp, so we recommend to return the exactly class pointer
  static cocos2d::CCScene *scene();

  // Implement the "static node()" method manually
  CREATE_FUNC(TitleScene);

  bool init();
  void update(float dt);
  void playAction(CCObject *sender);
  void howToPlayAction(CCObject *sender);
  void creditsAction(CCObject *sender);
  void musicSwitchAction(CCObject *sender);
  void quitAction(CCObject *sender);
  void logInAction(CCObject *sender);
  void logOutAction(CCObject *sender);

  void testAction(CCObject *sender);
};


#endif //__TitleScene_H_
