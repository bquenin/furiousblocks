//
// Created by bquenin on 2/24/13.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "ComputerPlayer.h"
#include "PanelHelper.h"
#include "ComboStarter.h"

ComputerPlayer::ComputerPlayer()
: cursorMoving(false) {
}

std::unique_ptr<Move>&& ComputerPlayer::onMoveRequest(const Panel& panel) {
  // Helper for the panel
  PanelHelper helper(panel);

  // Move to return
  auto move = std::unique_ptr<Move>();

  // The AI is too fast, just make it stop for a few frames
//      if (helper.isAnyBlockSwitching()) {
//        // Do nothing
//      }

  // If the cursor is moving to a target,
  // we just wait until it reaches its target.
  // Once the target is reached, we perform a block switch and process a new move
  if (cursorMoving) {
    move = moveCursorToCurrentTarget(panel);
  }
      // Check if we need to lift (Lifter)
      // Check if we need to level (Leveler)
      // If a combo is in progress, find a chain (ComboChainer)
      // Nothing is happening, find a combo starter (ComboStarter)
  else {
    ComboStarter comboStarter(helper);
    auto target = comboStarter.compute();
    if (target) {
      move = moveCursorToNewTarget(panel, *target);
    }
  }

  return std::move(move);
}

std::unique_ptr<Move> ComputerPlayer::moveCursorToNewTarget(const Panel& panel, const fb::Point& target) {
  auto move = std::unique_ptr<Move>();
  if (panel.cursor == targetPosition && cursorMoving) {
    cursorMoving = false;
    return move;
  }
  targetPosition = target;
  if (targetPosition.x > panel.X - 2) {
    targetPosition.x = panel.X - 2;
  }
  if (targetPosition.x < 0) {
    targetPosition.x = 0;
  }
  if (targetPosition.y > panel.Y_DISPLAY - 2) {
    targetPosition.y = panel.Y_DISPLAY - 2;
  }
  if (targetPosition.y < 1) {
    targetPosition.y = 1;
  }
  cursorMoving = true;
  return moveCursorToCurrentTarget(panel);
}

std::unique_ptr<Move> ComputerPlayer::moveCursorToCurrentTarget(const Panel& panel) {
  auto move = std::unique_ptr<Move>();
  if (panel.cursor.x < targetPosition.x) {
    move.reset(new Move(MoveType::CURSOR_RIGHT));
  } else if (panel.cursor.x > targetPosition.x) {
    move.reset(new Move(MoveType::CURSOR_LEFT));
  } else if (panel.cursor.y < targetPosition.y) {
    move.reset(new Move(MoveType::CURSOR_UP));
  } else if (panel.cursor.y > targetPosition.y) {
    move.reset(new Move(MoveType::CURSOR_DOWN));
  } else {
    cursorMoving = false;
    move.reset(new Move(MoveType::BLOCK_SWITCH));
  }
  return move;
}
