//
// Created by bquenin on 11/3/12.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __TutorialPlayer_H_
#define __TutorialPlayer_H_

#include <iostream>
#include "Player.h"
#include "MoveType.h"


class TutorialPlayer : public Player {
public:
  std::unique_ptr<Move> move;

  std::unique_ptr<Move>&& onMoveRequest(Panel const & panel) override;
  void setMove(MoveType moveType);
};

#endif //__TutorialPlayer_H_
