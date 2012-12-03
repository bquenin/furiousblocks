#include "Script.h"

Script *Script::add(std::unique_ptr<Action>&& action) {
  actions.push_back(std::move(action));
  return this;
}

void Script::clear() {
  actions.clear();
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
