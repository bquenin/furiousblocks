//
// Created by bquenin on 11/3/12.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "TouchPlayer.h"
#include "AbstractPanelScene.h"
#include "MoveType.h"
#include "Assets.h"

TouchPlayer::TouchPlayer()
: switchOnLeft(false)
, switchOnRight(false)
, leftTrend(false)
, rightTrend(false)
, upTrend(false)
, lifted(false)
, inputState(InputState::untouched) {
  cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, false);
}

bool TouchPlayer::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) {
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

void TouchPlayer::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) {
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

  if ((touchPointDragged.x - AbstractPanelScene::xOffset) < (touchPointDown.x - AbstractPanelScene::xOffset) - ((static_cast<int32_t>(touchPointDown.x) - AbstractPanelScene::xOffset) % Assets::TILE_SIZE)) {
    switchOnLeft = true;
    switchOnRight = false;
  } else if ((touchPointDragged.x - AbstractPanelScene::xOffset) > (touchPointDown.x - AbstractPanelScene::xOffset) + (Assets::TILE_SIZE - (static_cast<int32_t>(touchPointDown.x - AbstractPanelScene::xOffset) % Assets::TILE_SIZE))) {
    switchOnLeft = false;
    switchOnRight = true;
  }
}

void TouchPlayer::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) {
  inputState = InputState::untouched;
  switchOnLeft = false;
  switchOnRight = false;
  leftTrend = false;
  rightTrend = false;
  upTrend = false;
  lifted = false;
}

std::unique_ptr<Move, MoveDeleter> TouchPlayer::onMoveRequest(const Panel &panel) {
  int32_t const x = static_cast<int32_t> (AbstractPanelScene::xOffset + (Assets::TILE_SIZE * panel.cursor->x));
  int32_t const y = static_cast<int32_t> (AbstractPanelScene::yOffset + (Assets::TILE_SIZE * panel.cursor->y) + ((panel.scrollingDelta * Assets::TILE_SIZE) / FuriousBlocksCoreDefaults::BLOCK_LOGICALHEIGHT));
  cocos2d::CCRect cursorPosition(x + (leftTrend ? Assets::TILE_SIZE : 0), y, Assets::TILE_SIZE, Assets::TILE_SIZE);
  cocos2d::CCPoint aPoint(touchPointDragged.x + (leftTrend ? Assets::TILE_SIZE : 0) - (rightTrend ? Assets::TILE_SIZE : 0), touchPointDragged.y);
  if (upTrend && !lifted) {
    lifted = true;
    return std::unique_ptr<Move, MoveDeleter>(new Move(MoveType::LIFT));
  } else if (cursorPosition.containsPoint(aPoint) && (switchOnLeft || switchOnRight)) {
    touchPointDown = touchPointDragged;
    switchOnLeft = false;
    switchOnRight = false;
    return std::unique_ptr<Move, MoveDeleter>(new Move(MoveType::BLOCK_SWITCH));
  } else if (touchPointDown.x < cursorPosition.origin.x) {
    return std::unique_ptr<Move, MoveDeleter>(new Move(MoveType::CURSOR_LEFT));
  } else if (touchPointDown.x > cursorPosition.origin.x + cursorPosition.size.width) {
    return std::unique_ptr<Move, MoveDeleter>(new Move(MoveType::CURSOR_RIGHT));
  } else if (touchPointDown.y < cursorPosition.origin.y) {
    return std::unique_ptr<Move, MoveDeleter>(new Move(MoveType::CURSOR_DOWN));
  } else if (touchPointDown.y > cursorPosition.origin.y + cursorPosition.size.height) {
    return std::unique_ptr<Move, MoveDeleter>(new Move(MoveType::CURSOR_UP));
  }
  return std::unique_ptr<Move, MoveDeleter>(nullptr);
}
