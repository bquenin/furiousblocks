#ifndef __SetBlocksAction_H_
#define __SetBlocksAction_H_

#include "Action.h"
#include "Panel.h"

class SetBlocksAction : public Action {
private:
  Panel *panel;
  BlockType **blockTypes;
  size_t xLen;
  size_t yLen;

protected:
public:
  SetBlocksAction(float timeStep, Panel *panel, BlockType **blockTypes, size_t xLen, size_t yLen);
  bool execute(float stateTime);
};

#endif //__SetBlocksAction_H_
