#ifndef __TutorialPlayer_H_
#define __TutorialPlayer_H_

#include <cstdint>
#include "Player.h"

class TutorialPlayer : Player
{
private:
protected:
  Move *onMoveRequest(const Panel &panel);

public:
    TutorialPlayer(String* name);
    void setMove(int8_t moveType);
};

#endif //__TutorialPlayer_H_
