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
  static constexpr float TILE_SIZE = 48;

  InputState inputState;
  int32_t id;
  Move *move;
  bool rightTrend;
  bool leftTrend;
  bool switchOnRight;
  bool switchOnLeft;
  CCPoint touchPointDown;
  CCPoint touchPointDragged;

  Player(int32_t id = 123);
  bool ccTouchBegan(CCTouch *touch, CCEvent *event);
  void ccTouchMoved(CCTouch *touch, CCEvent *event);
  void ccTouchEnded(CCTouch *touch, CCEvent *event);
  void onSituationUpdate(PanelSituation *panelSituation);
  Move *onMoveRequest();
};

#endif //__Player_H_
