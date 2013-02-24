//
// Created by bquenin on 2/24/13.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __ComputerPlayer_H_
#define __ComputerPlayer_H_

#include <iostream>
#include "Player.h"

class ComputerPlayer : public Player {
public:
  ComputerPlayer();

  virtual std::unique_ptr<Move>&& onMoveRequest(const Panel& panel) override;

  std::unique_ptr<Move> moveCursorToCurrentTarget(const Panel& panel);
  std::unique_ptr<Move> moveCursorToNewTarget(const Panel& panel, const fb::Point& target);

  bool cursorMoving;
  fb::Point targetPosition;
};

#endif //__ComputerPlayer_H_
