#ifndef __Player_H_
#define __Player_H_

#include <cstdint>
#include <string>
#include "PanelSituation.h"
#include "Move.h"
#include "cocos2d.h"

USING_NS_CC;

enum class InputState {
  untouched,
  touched
};

class Player : public CCObject, public CCTouchDelegate {
public:
  InputState inputState;
  int32_t id;
  Player(int32_t id = 123);
  //    Move* onMoveRequest();
  //    void onSituationUpdate(PanelSituation* panelSituation);
  //    void run();
  bool ccTouchBegan(CCTouch *touch, CCEvent *event);
  void ccTouchMoved(CCTouch *touch, CCEvent *event);
  void ccTouchEnded(CCTouch *touch, CCEvent *event);
  void onSituationUpdate(PanelSituation *panelSituation);
  bool rightTrend;
  bool leftTrend;
  bool switchOnRight;
  bool switchOnLeft;
  CCPoint touchPointDown;
  CCPoint touchPointDragged;
  void playerTick(PanelSituation panelSituation, bool isMostRecentData);
  static constexpr float TILE_SIZE = 48;
};

#endif //__Player_H_
