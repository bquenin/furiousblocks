//
// Created by bquenin on 11/3/12.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __TouchPlayer_H_
#define __TouchPlayer_H_

#include <iostream>
#include "Player.h"
#include "cocos2d.h"

class TouchPlayer : public Player, public cocos2d::CCObject, public cocos2d::CCTouchDelegate {
public:
  TouchPlayer();

private:
  enum class InputState {
    untouched,
    touched
  };

  bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
  void ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
  void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);

  InputState inputState;
  bool rightTrend;
  bool leftTrend;
  bool upTrend;
  bool switchOnRight;
  bool switchOnLeft;
  bool lifted;
  cocos2d::CCPoint touchPointDown;
  cocos2d::CCPoint touchPointDragged;
  std::unique_ptr<Move, MoveDeleter> onMoveRequest(Panel const & panel);
};

#endif //__TouchPlayer_H_
