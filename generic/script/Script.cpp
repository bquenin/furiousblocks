#include "Script.h"

Script *Script::add(Action *action) {
  actions.push_back(action);
  return this;
}

void Script::empty() {
  actions.erase(actions.begin(), actions.end());
}

void Script::execute(float stateTime) {
  if (actions.empty()) {
    return;
  }
  auto action = actions.begin();
  if ((*action)->execute(stateTime)) {
    actions.erase(action);
    if (actions.empty()) {
      return;
    }
    auto nextAction = actions.begin();
    (*nextAction)->setNextStep(stateTime + (*action)->getTimeStep());
  }
}
