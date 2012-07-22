#include "Player.h"
using namespace std;

Player::Player(int id, String* name)
:id(0), name(nullptr), move(new AtomicReference<Move*>()), situations(new LinkedBlockingQueue<PanelSituation*>())
{
    this->id = id;
    this->name = name;
}

Player::Player(String* name)
:id(0), name(nullptr), move(new AtomicReference<Move*>()), situations(new LinkedBlockingQueue<PanelSituation*>())
{
    Player(Player::RANDOM->nextInt(), name);
}

int Player::getId()
{
    return id;
}

String* Player::getName()
{
    return name;
}

Move* Player::onMoveRequest()
{
    return move->getAndSet(nullptr);
}

void Player::onSituationUpdate(PanelSituation* panelSituation)
{
    situations->add(panelSituation);
}

void Player::run()
{
}

int Player::hashCode()
{
    int prime = 31;
    int result = 1;
    result = (prime * result) + id;
    return result;
}

bool Player::equals(Object* obj)
{
    if (this == obj){
        return true;
    }
    if (obj == nullptr){
        return false;
    }
    if (getClass() != obj->getClass()){
        return false;
    }
    Player* other = TODO CastExpression;
    return id == other->id;
}
