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
  Player *player;

  // Labels
  cocos2d::CCLabelBMFont *score;
  cocos2d::CCLabelBMFont *minutes;
  cocos2d::CCLabelBMFont *seconds;
  cocos2d::CCLabelBMFont *centisecs;

  // Opening
  int countdown;
  cocos2d::CCLabelBMFont *countdownLabel;

  // Gameover
  cocos2d::CCSprite *youLose;

  // Menu
//  InputState inputState;
  CCControlButton *menuButton;
  PanelMenuOverlay *panelMenuOverlay;

public:
  // Implement the "static node()" method manually
  CREATE_FUNC(PanelScene);

  // there's no 'id' in cpp, so we recommend to return the exactly class pointer
  static cocos2d::CCScene *scene();

  PanelScene();
  bool init();
  void update(float d);
  void onCombo(Combo *combo);
  void onGameOver();
  void onBeginningTweenFinished(void);
  void menuAction(CCObject *sender);
  void setOverlay(PanelMenuOverlay *panelMenuOverlay);

  void registerWithTouchDispatcher();
  bool ccTouchBegan(CCTouch *touch, CCEvent *event);
  void ccTouchEnded(CCTouch *touch, CCEvent *event);
};

#endif // __PANELSCENE_H_
