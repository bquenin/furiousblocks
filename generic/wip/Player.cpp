#include <cstdint>
#include "PanelSituation.h"
#include "Player.h"

using namespace std;

Player::Player(int32_t id, string& name)
: id(id), name(name) {
}

//Player::Player(string& name)
//{
//    Player(Player::RANDOM.nextInt(), name);
//}

//int32_t Player::getId()
//{
//    return id;
//}
//
//string& Player::getName()
//{
//    return name;
//}

//Move& Player::onMoveRequest()
//{
//    return move.getAndSet(nullptr);
//}
//
//void Player::onSituationUpdate(PanelSituation& panelSituation)
//{
//    situations.add(panelSituation);
//}
//
//void Player::run()
//{
//}
