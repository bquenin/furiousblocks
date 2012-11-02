#include <cstdint>
#include "TutorialPlayer.h"

TutorialPlayer::TutorialPlayer(String* name)
{
}

void TutorialPlayer::setMove(int8_t moveType)
{
    this->move = new Move(moveType);
}

void TutorialPlayer::playerTick(PanelSituation* panelSituation, bool isMostRecentData)
{
}
