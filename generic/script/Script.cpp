#include <list>
#include "Script.h"

Script* Script::add(Action* action)
{
    actions->add(action);
    return this;
}

void Script::execute(float stateTime)
{
    Action* action = actions->peek();
    if (action == nullptr){
        return;
    }
    if (action->execute(stateTime)){
        actions->remove();
        Action* nextAction = actions->peek();
        if (nextAction == nullptr){
            return;
        }
        nextAction->setNextStep(stateTime + action->getTimeStep());
    }
}
