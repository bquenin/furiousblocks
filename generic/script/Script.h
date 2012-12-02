#ifndef __Script_H_
#define __Script_H_

#include <vector>
#include "Action.h"

class Script {
private:
  std::vector<Action *> actions;

protected:
public:
  Script *add(Action *action);
  void execute(float stateTime);
  void empty();
};

#endif //__Script_H_
