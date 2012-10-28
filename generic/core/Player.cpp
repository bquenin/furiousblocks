#include <cstdint>
#include "Player.h"
#include "PanelScene.h"
#include "MoveType.h"

Player::Player(int32_t id)
: id(id)
, switchOnLeft(false)
, switchOnRight(false)
, leftTrend(false)
, rightTrend(false)
, upTrend(false)
, lifted(false)
, inputState(InputState::untouched) {
  cocos2d::CCDirector *pDirector = cocos2d::CCDirector::sharedDirector();
  pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool Player::ccTouchBegan(CCTouch *touch, CCEvent *event) {
  if (inputState != InputState::untouched) {
    return false;
  }

  inputState = InputState::touched;

  touchPointDown = touch->getLocation();
  touchPointDragged = touch->getLocation();
  switchOnLeft = false;
  switchOnRight = false;
  leftTrend = false;
  rightTrend = false;
  upTrend = false;

  return true;
}

void Player::ccTouchMoved(CCTouch *touch, CCEvent *event) {
  if (switchOnLeft || switchOnRight || upTrend) {
    return;
  }
  touchPointDragged = touch->getLocation();
  if (touchPointDragged.x < touchPointDown.x) {
    leftTrend = true;
    rightTrend = false;
    upTrend = false;
  } else if (touchPointDragged.x > touchPointDown.x) {
    leftTrend = false;
    rightTrend = true;
    upTrend = false;
  }

  if (touchPointDragged.y > touchPointDown.y + 32) {
    upTrend = true;
  }

  if ((touchPointDragged.x - PanelScene::xOffset) < (touchPointDown.x - PanelScene::xOffset) - ((static_cast<int32_t>(touchPointDown.x) - PanelScene::xOffset) % PanelScene::TILE_SIZE)) {
    switchOnLeft = true;
    switchOnRight = false;
  } else if ((touchPointDragged.x - PanelScene::xOffset) > (touchPointDown.x - PanelScene::xOffset) + (PanelScene::TILE_SIZE - (static_cast<int32_t>(touchPointDown.x - PanelScene::xOffset) % PanelScene::TILE_SIZE))) {
    switchOnLeft = false;
    switchOnRight = true;
  }
}

void Player::ccTouchEnded(CCTouch *touch, CCEvent *event) {
  inputState = InputState::untouched;
  switchOnLeft = false;
  switchOnRight = false;
  leftTrend = false;
  rightTrend = false;
  upTrend = false;
  lifted = false;
}

Move *Player::onMoveRequest(const Panel &panel) {
  Move *move = nullptr;
  if (inputState != InputState::touched) {
    return move;
  }
  //      CCLOG("touchPointDown = %f/%f", touchPointDown.x, touchPointDown.y);
  int32_t const x = static_cast<int32_t> (PanelScene::xOffset + (PanelScene::TILE_SIZE * panel.cursor->x));
  int32_t const y = static_cast<int32_t> (PanelScene::yOffset + (PanelScene::TILE_SIZE * panel.cursor->y) + ((panel.scrollingDelta * PanelScene::TILE_SIZE) / FuriousBlocksCoreDefaults::BLOCK_LOGICALHEIGHT));
  CCRect cursorPosition(x + (leftTrend ? PanelScene::TILE_SIZE : 0), y, PanelScene::TILE_SIZE, PanelScene::TILE_SIZE);
  CCPoint aPoint(touchPointDragged.x + (leftTrend ? PanelScene::TILE_SIZE : 0) - (rightTrend ? PanelScene::TILE_SIZE : 0), touchPointDragged.y);
  if (upTrend && !lifted) {
    move = new Move(MoveType::LIFT);
    lifted = true;
  } else if (cursorPosition.containsPoint(aPoint) && (switchOnLeft || switchOnRight)) {
    move = new Move(MoveType::BLOCK_SWITCH);
    //          camera.unproject(touchPointDown.set(Gdx.input.getX(), Gdx.input.getY(), 0));
    touchPointDown = touchPointDragged;
    switchOnLeft = false;
    switchOnRight = false;
  } else if (touchPointDown.x < cursorPosition.origin.x) {
    move = new Move(MoveType::CURSOR_LEFT);
  } else if (touchPointDown.x > cursorPosition.origin.x + cursorPosition.size.width) {
    move = new Move(MoveType::CURSOR_RIGHT);
  } else if (touchPointDown.y < cursorPosition.origin.y) {
    move = new Move(MoveType::CURSOR_DOWN);
  } else if (touchPointDown.y > cursorPosition.origin.y + cursorPosition.size.height) {
    move = new Move(MoveType::CURSOR_UP);
  }
  return move;
}
