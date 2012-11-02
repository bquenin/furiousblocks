#ifndef __TypeTextAction_H_
#define __TypeTextAction_H_

#include <cstdint>

class TypeTextAction : Action
{
private:
    String* text = nullptr;
    TextToType* out = nullptr;
    int32_t index = 0;

protected:
public:
    TypeTextAction(float timeStep, String* text, TextToType* out);
    bool execute(float stateTime);
};

#endif //__TypeTextAction_H_
