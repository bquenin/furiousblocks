#ifndef __SetBlocksAction_H_
#define __SetBlocksAction_H_

#include "Action.h"
#include "Panel.h"

class SetBlocksAction : public Action {
private:
  Panel &panel;
  const std::vector<const std::vector<BlockType>> &blockTypes;

protected:
public:
  SetBlocksAction(float timeStep, Panel &panel, const std::vector<const std::vector<BlockType>> &blockTypes);
  bool execute(float stateTime);
};

#endif //__SetBlocksAction_H_
