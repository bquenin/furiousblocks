#include "PanelSituation.h"
#include "Channel.h"
#include "LobbyPlayer.h"
#include "Move.h"
#include "NetworkPlayer.h"

NetworkPlayer::NetworkPlayer(LobbyPlayer& lobbyPlayer, Channel& channel) {
  this->channel = channel;
}

NetworkPlayer::NetworkPlayer(LobbyPlayer& lobbyPlayer) {
  NetworkPlayer(lobbyPlayer, nullptr);
}

Channel& NetworkPlayer::getChannel() {
  return channel;
}

void NetworkPlayer::submitMove(Move& move) {
  this->move.set(move);
}

void NetworkPlayer::playerTick(PanelSituation& panelSituation, bool isMostRecentData) {
}
