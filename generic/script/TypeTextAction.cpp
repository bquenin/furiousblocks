#include <cstdint>
#include "TypeTextAction.h"

TypeTextAction::TypeTextAction(float timeStep, std::string text, TextToType &out)
: Action(timeStep)
, text(text)
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
