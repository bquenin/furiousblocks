#ifndef __TypeTextAction_H_
#define __TypeTextAction_H_

#include <cstdint>
#include <string>
#include "Action.h"
#include "TextToType.h"

class TypeTextAction : public Action {
private:
  const std::string text;
  TextToType &out;
  size_t index;

protected:
public:
  TypeTextAction(float timeStep, const std::string&& text, TextToType &out);
  bool execute(float stateTime);
};

#endif //__TypeTextAction_H_
