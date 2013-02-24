#ifndef __Script_H_
#define __Script_H_

#include <vector>
#include "Action.h"

class Script {
private:
  std::vector<std::unique_ptr<Action>> actions;

public:
  void add(std::unique_ptr<Action>&& action);
  void execute(float stateTime);
};

#endif //__Script_H_
