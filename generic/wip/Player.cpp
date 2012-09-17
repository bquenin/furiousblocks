#include <cstdint>
#include "Player.h"
#include "MoveType.h"
#include "PanelScene.h"

Player::Player(int32_t id)
: id(id)
, inputState(InputState::untouched) {
  cocos2d::CCDirector *pDirector = cocos2d::CCDirector::sharedDirector();
  pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool Player::ccTouchBegan(CCTouch *touch, CCEvent *event) {
  if (inputState != InputState::untouched) {
    return false;
  }

  //  if (!containsTouchLocation(touch)) {
  //    return false;
  //  }
  //
  inputState = InputState::touched;

  touchPointDown = touch->getLocation();
  touchPointDragged = touch->getLocation();
  switchOnLeft = false;
  switchOnRight = false;
  leftTrend = false;
  rightTrend = false;

//  CCLOG("touchPointDown = %f/%f", touchPointDown.x, touchPointDown.y);

  return true;
}

void Player::ccTouchMoved(CCTouch *touch, CCEvent *event) {
  if (switchOnLeft || switchOnRight) {
    return;
  }
  touchPointDragged = touch->getLocation();
  if (touchPointDragged.x < touchPointDown.x) {
    leftTrend = true;
    rightTrend = false;
  } else if (touchPointDragged.x > touchPointDown.x) {
    leftTrend = false;
    rightTrend = true;
  }
  if ((touchPointDragged.x - PanelScene::xOffset) < (touchPointDown.x - PanelScene::xOffset) - ((touchPointDown.x - PanelScene::xOffset) / TILE_SIZE)) {
    switchOnLeft = true;
    switchOnRight = false;
  } else if ((touchPointDragged.x - PanelScene::xOffset) > (touchPointDown.x - PanelScene::xOffset) + (TILE_SIZE - ((touchPointDown.x - PanelScene::xOffset) / TILE_SIZE))) {
    switchOnLeft = false;
    switchOnRight = true;
  }
}

void Player::ccTouchEnded(CCTouch *touch, CCEvent *event) {
  //  CCAssert(m_state == kPaddleStateGrabbed, L"Paddle - Unexpected state!");
  //
  //  m_state = kPaddleStateUngrabbed;
  inputState = InputState::untouched;

  switchOnLeft = false;
  switchOnRight = false;
  leftTrend = false;
  rightTrend = false;
}

void Player::onSituationUpdate(PanelSituation *panelSituation) {
  if (inputState != InputState::touched) {
    if (move != nullptr) {
      delete move;
      move = nullptr;
    }
    return;
  }
  CCLOG("touchPointDown = %f/%f", touchPointDown.x, touchPointDown.y);
  float const x = PanelScene::xOffset + (TILE_SIZE * panelSituation->cursorPosition.x);
  float const y = PanelScene::yOffset + (TILE_SIZE * panelSituation->cursorPosition.y) + ((panelSituation->scrollingOffset * TILE_SIZE) / FuriousBlocksCoreDefaults::BLOCK_LOGICALHEIGHT);
  CCRect cursorPosition(x /*+ (leftTrend ? TILE_SIZE : 0)*/, y, TILE_SIZE, TILE_SIZE);
//  CCPoint aPoint(touchPointDragged.x + (leftTrend ? TILE_SIZE : 0) - (rightTrend ? TILE_SIZE : 0), touchPointDragged.y);
//  if (cursorPosition.containsPoint(aPoint) && (switchOnLeft || switchOnRight)) {
//    move = new Move(MoveType::BLOCK_SWITCH);
//    //          camera.unproject(touchPointDown.set(Gdx.input.getX(), Gdx.input.getY(), 0));
//    touchPointDown = touchPointDragged;
//    switchOnLeft = false;
//    switchOnRight = false;
//  } else
  if (touchPointDown.x < cursorPosition.origin.x) {
//    move = new Move(MoveType::CURSOR_LEFT);
    CCLOG("LEFT");
  } else if (touchPointDown.x > cursorPosition.origin.x + cursorPosition.size.width) {
//    move = new Move(MoveType::CURSOR_RIGHT);
    CCLOG("RIGHT");
  } else if (touchPointDown.y < cursorPosition.origin.y) {
    CCLOG("DOWN");
//    move = new Move(MoveType::CURSOR_DOWN);
  } else if (touchPointDown.y > cursorPosition.origin.y + cursorPosition.size.height) {
    CCLOG("UP");
//    move = new Move(MoveType::CURSOR_UP);
  }
}

Move *Player::onMoveRequest() {
  return move;
}
