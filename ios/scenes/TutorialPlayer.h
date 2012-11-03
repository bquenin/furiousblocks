//
// Created by bquenin on 11/3/12.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __TutorialPlayer_H_
#define __TutorialPlayer_H_

#include <iostream>
#include "Player.h"


class TutorialPlayer : public Player {
public:
  std::unique_ptr<Move> move;

  std::unique_ptr<Move> onMoveRequest(Panel const & panel);
  void setMove(int8_t moveType);
};

#endif //__TutorialPlayer_H_
