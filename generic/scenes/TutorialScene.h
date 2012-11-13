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
#include "BlockType.h"
#include "Script.h"
#include "TextToType.h"
#include "TutorialPlayer.h"

class TutorialScene : public AbstractPanelScene, FuriousBlocksCoreListener {
private:
  static std::vector<std::vector<BlockType> > empty;
  static std::vector<std::vector<BlockType> > combo4and5;
  static std::vector<std::vector<BlockType> > combo6and10;
  static std::vector<std::vector<BlockType> > chainx2;
  static std::vector<std::vector<BlockType> > chainx3;
  static std::vector<std::vector<BlockType> > etc4ChainsPanel;

  Script script;
  TutorialPlayer *tutorialPlayer;
  TextToType textToType;
  cocos2d::CCLabelBMFont *textBox;
  cocos2d::CCSprite *cursor;

public:
  TutorialScene();
  bool init();
  void update(float dt);
  void onCombo(Combo *combo);
  void onGameOver();

  // there's no 'id' in cpp, so we recommend to return the exactly class pointer
  static cocos2d::CCScene *scene();

  // Implement the "static node()" method manually
  CREATE_FUNC(TutorialScene);
};

#endif //__TutorialScene_H_
