#include <cstdint>
#include "Player.h"


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
  CCLOG("inputState = %d", inputState);

  touchPointDown = touch->getLocation();
  touchPointDragged = touch->getLocation();
  switchOnLeft = false;
  switchOnRight = false;
  leftTrend = false;
  rightTrend = false;

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
  if ((touchPointDragged.x - 16) < (touchPointDown.x - 16) - ((touchPointDown.x - 16) / TILE_SIZE)) {
    switchOnLeft = true;
    switchOnRight = false;
  } else if ((touchPointDragged.x - 16) > (touchPointDown.x - 16) + (TILE_SIZE - ((touchPointDown.x - 16) / TILE_SIZE))) {
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

  CCLOG("inputState = %d", inputState);
}

void Player::playerTick(PanelSituation panelSituation, bool isMostRecentData) {
  if (inputState == InputState::touched) {
    float const x = 16 + (TILE_SIZE * panelSituation.cursorPosition.x);
    float const y = -48 + (TILE_SIZE * panelSituation.cursorPosition.y) + ((panelSituation.scrollingOffset * TILE_SIZE) / FuriousBlocksCoreDefaults::BLOCK_LOGICALHEIGHT);
        CCRect cursorPosition(x + (leftTrend ? TILE_SIZE : 0), y, TILE_SIZE, TILE_SIZE);
        CCPoint aPoint(touchPointDragged.x + (leftTrend ? TILE_SIZE : 0) - (rightTrend ? TILE_SIZE : 0), touchPointDragged.y);
        if (cursorPosition.containsPoint(aPoint) && (switchOnLeft || switchOnRight)) {
//          move = new Move(BLOCK_SWITCH);
//          camera.unproject(touchPointDown.set(Gdx.input.getX(), Gdx.input.getY(), 0));
          touchPointDown = touchPointDragged;
          switchOnLeft = false;
          switchOnRight = false;
        } else if (touchPointDown.x < cursorPosition.origin.x) {
//          move = new Move(CURSOR_LEFT);
        } else if (touchPointDown.x > cursorPosition.origin.x + cursorPosition.size.width) {
//          move = new Move(CURSOR_RIGHT);
        } else if (touchPointDown.y < cursorPosition.origin.y) {
//          move = new Move(CURSOR_DOWN);
        } else if (touchPointDown.y > cursorPosition.origin.y + cursorPosition.size.height) {
//          move = new Move(CURSOR_UP);
        }
  }
}


void Player::onSituationUpdate(PanelSituation *panelSituation) {
}
