#ifndef __PANELSCENE_H_
#define __PANELSCENE_H_

#include <array>
#include <unordered_map>
#include "AbstractPanelScene.h"
#include "FuriousBlocksCore.h"
#include "NonLoopingAnimation.h"
#include "tweener_group.hpp"
#include "single_tweener.hpp"

class PanelScene : public AbstractPanelScene, FuriousBlocksCoreListener {
private:
  Player *player;
  // Labels
  cocos2d::CCLabelBMFont *score;
  cocos2d::CCLabelBMFont *minutes;
  cocos2d::CCLabelBMFont *seconds;
  cocos2d::CCLabelBMFont *centisecs;

  // Gameover
  cocos2d::CCSprite *youLose;

public:
  PanelScene();
  bool init();
  void update(float d);
  void onCombo(Combo *combo);
  void onGameOver();
  void onBeginningTweenFinished(void);

  // there's no 'id' in cpp, so we recommend to return the exactly class pointer
  static cocos2d::CCScene *scene();

  // Implement the "static node()" method manually
  CREATE_FUNC(PanelScene);

  // Countdown
  int countdown = 3;
  cocos2d::CCLabelBMFont *countdownLabel;
};

#endif // __PANELSCENE_H_
