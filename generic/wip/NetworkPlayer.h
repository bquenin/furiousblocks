#ifndef __NetworkPlayer_H_
#define __NetworkPlayer_H_

#include "PanelSituation.h"
#include "Move.h"
#include "Player.h"

class NetworkPlayer : Player {
private:
  Channel& channel = nullptr;

protected:
  void playerTick(PanelSituation& panelSituation, bool isMostRecentData);

public:
  bool ready = false;
  NetworkPlayer(LobbyPlayer& lobbyPlayer, Channel& channel);
  NetworkPlayer(LobbyPlayer& lobbyPlayer);
  Channel& getChannel();
  void submitMove(Move& move);
};

#endif //__NetworkPlayer_H_
