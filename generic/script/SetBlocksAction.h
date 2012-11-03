#ifndef __SetBlocksAction_H_
#define __SetBlocksAction_H_

#include "Action.h"
#include "Panel.h"

class SetBlocksAction : Action
{
private:
    Panel* panel = nullptr;
    BlockType*** blockTypes = nullptr;

protected:
public:
    SetBlocksAction(float timeStep, Panel* panel, BlockType*** blockTypes);
    bool execute(float stateTime);
};

#endif //__SetBlocksAction_H_
