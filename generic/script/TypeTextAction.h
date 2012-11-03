#ifndef __TypeTextAction_H_
#define __TypeTextAction_H_

#include <cstdint>
#include <string>
#include "Action.h"
#include "TextToType.h"

class TypeTextAction : Action {
private:
  std::string text = nullptr;
  TextToType *out = nullptr;
  size_t index = 0;

protected:
public:
  TypeTextAction(float timeStep, std::string text, TextToType *out);
  bool execute(float stateTime);
};

#endif //__TypeTextAction_H_
