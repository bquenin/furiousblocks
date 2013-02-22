#include "Script.h"

Script* Script::add(Action* action) {
  actions.push_back(action);
  return this;
}

void Script::clear() {
  for (auto action : actions) {
    delete action;
  }
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
