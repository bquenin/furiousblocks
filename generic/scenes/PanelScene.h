//
// Created by bquenin on 11/12/12.
//
// To change the template use AppCode | Preferences | File Templates.
//

#ifndef __PANELSCENE_H_
#define __PANELSCENE_H_

#include "AbstractPanelScene.h"
#include "FuriousBlocksCore.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "PanelMenuOverlay.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class PanelScene : public AbstractPanelScene, FuriousBlocksCoreListener {
private:
  Player* player;

  // Labels
  CCLabelBMFont* level;
  CCLabelBMFont* score;
  CCLabelBMFont* minutes;
  CCLabelBMFont* seconds;
  CCLabelBMFont* centisecs;
#if DEBUG
  CCSprite* cursor;
#endif

  // Opening
  int countdown;
  CCLabelBMFont* countdownLabel;

  // Gameover
  CCSprite* youLose;

  // Menu
//  InputState inputState;
  CCControlButton* menuButton;
  PanelMenuOverlay* panelMenuOverlay;

public:
  bool gameOver;
  // Implement the "static node()" method manually
  CREATE_FUNC(PanelScene);

  // there's no 'id' in cpp, so we recommend to return the exactly class pointer
  static CCScene* scene();

  PanelScene();
  ~PanelScene();
  bool init();
  void update(float d);
  void onCombo(Combo* combo);
  void onGameOver();
  void onBeginningTweenFinished(void);
  void menuAction(CCObject* sender);
  void setOverlay(PanelMenuOverlay* panelMenuOverlay);
  void onLastStepFinished(void);

  void registerWithTouchDispatcher();
  bool ccTouchBegan(CCTouch* touch, CCEvent* event);
  void ccTouchEnded(CCTouch* touch, CCEvent* event);
};

#endif // __PANELSCENE_H_
