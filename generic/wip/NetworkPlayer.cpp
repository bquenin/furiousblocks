#include "NetworkPlayer.h"
using namespace std;

NetworkPlayer::NetworkPlayer(LobbyPlayer* lobbyPlayer, Channel* channel)
:ready(false), channel(nullptr)
{
    this->channel = channel;
}

NetworkPlayer::NetworkPlayer(LobbyPlayer* lobbyPlayer)
:ready(false), channel(nullptr)
{
    NetworkPlayer(lobbyPlayer, nullptr);
}

Channel* NetworkPlayer::getChannel()
{
    return channel;
}

void NetworkPlayer::submitMove(Move* move)
{
    this->move.set(move);
}

void NetworkPlayer::playerTick(PanelSituation* panelSituation, bool isMostRecentData)
{
}
