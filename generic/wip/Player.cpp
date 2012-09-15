#include <cstdint>
#include "Player.h"

Player::Player(int32_t id, const std::string name)
: id(id)
, name(name) {
}

void Player::onSituationUpdate(PanelSituation *panelSituation) {
}
