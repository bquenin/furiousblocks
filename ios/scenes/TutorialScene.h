//
// Created by bquenin on 11/2/12.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __TutorialScene_H_
#define __TutorialScene_H_

#include <iostream>
#include "AbstractPanelScene.h"
#include "FuriousBlocksCoreListener.h"

class TutorialScene : public AbstractPanelScene, FuriousBlocksCoreListener {
private:
  Player *player;

public:
  TutorialScene();
  bool init();
  void update(float d);
  void onCombo(Combo *combo);
  void onGameOver();
  //  void onBeginningTweenFinished(void);

  // there's no 'id' in cpp, so we recommend to return the exactly class pointer
  static cocos2d::CCScene *scene();

  // Implement the "static node()" method manually
  CREATE_FUNC(TutorialScene);
};

#endif //__TutorialScene_H_
