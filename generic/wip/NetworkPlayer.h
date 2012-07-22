#ifndef __NetworkPlayer_H_
#define __NetworkPlayer_H_
#include "Channel.h"
#include "PanelSituation.h"
#include "LobbyPlayer.h"
#include "Player.h"
#include "Move.h"
using namespace std;
class NetworkPlayer
{
public:
    bool ready;
    NetworkPlayer(LobbyPlayer* lobbyPlayer, Channel* channel);
    NetworkPlayer(LobbyPlayer* lobbyPlayer);
    Channel* getChannel();
    void submitMove(Move* move);

protected:
    void playerTick(PanelSituation* panelSituation, bool isMostRecentData);

private:
    Channel* channel;
};
#endif //__NetworkPlayer_H_
