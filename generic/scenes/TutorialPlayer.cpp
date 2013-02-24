//
// Created by bquenin on 11/3/12.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "TutorialPlayer.h"

void TutorialPlayer::setMove(MoveType moveType) {
  move.reset(new Move(moveType));
}

std::unique_ptr<Move> TutorialPlayer::onMoveRequest(const Panel& panel) {
  return std::move(move);
}
