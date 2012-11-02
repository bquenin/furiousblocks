#ifndef __PANELSCENE_H_
#define __PANELSCENE_H_

#include <array>
#include <unordered_map>
#include "FuriousBlocksCore.h"
#include "NonLoopingAnimation.h"
#include "tweener_group.hpp"
#include "single_tweener.hpp"
#include "AbstractPanelScene.h"

class PanelScene : public AbstractPanelScene, FuriousBlocksCoreListener {
private:
  Player *player;

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
};

#endif // __PANELSCENE_H_
