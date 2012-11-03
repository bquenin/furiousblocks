#include <cstdint>
#include "TypeTextAction.h"

TypeTextAction::TypeTextAction(float timeStep, std::string text, TextToType *out) {
  this->timeStep = timeStep;
  this->text = text;
  this->out = out;
}

bool TypeTextAction::execute(float stateTime) {
  if (stateTime > nextStep) {
    if (index == text.length()) {
      return true;
    } else {
      index++;
      out->setText(text.substr(0, index));
    }
    nextStep = stateTime + timeStep;
  }
  return false;
}
