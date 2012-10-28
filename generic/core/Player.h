#ifndef __Player_H_
#define __Player_H_

#include <cstdint>
#include <string>
#include "Move.h"
#include "cocos2d.h"
#include "Panel.h"

USING_NS_CC;

enum class InputState {
  untouched,
  touched
};

class Player : public CCObject, public CCTouchDelegate {
public:
  InputState inputState;
  int32_t id;
  bool rightTrend;
  bool leftTrend;
  bool upTrend;
  bool switchOnRight;
  bool switchOnLeft;
  bool lifted;
  CCPoint touchPointDown;
  CCPoint touchPointDragged;

  Player(int32_t id = 123);
  bool ccTouchBegan(CCTouch *touch, CCEvent *event);
  void ccTouchMoved(CCTouch *touch, CCEvent *event);
  void ccTouchEnded(CCTouch *touch, CCEvent *event);
  Move *onMoveRequest(const Panel &panel);
};

#endif //__Player_H_
