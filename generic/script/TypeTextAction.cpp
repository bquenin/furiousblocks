#include <cstdint>
#include "TypeTextAction.h"
#include "cocos2d.h"

using namespace cocos2d;

TypeTextAction::TypeTextAction(float timeStep, const std::string &&text, TextToType &out)
: Action(timeStep)
, text(std::move(text))
, out(out)
, index(0) {
}

bool TypeTextAction::execute(float stateTime) {
  if (stateTime > nextStep) {
    if (index == text.length()) {
      return true;
    } else {
      index++;
      out.setText(text.substr(0, index));
    }
    nextStep = stateTime + timeStep;
  }
  return false;
}
