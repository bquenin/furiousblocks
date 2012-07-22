#ifndef __StackGarbageEvent_H_
#define __StackGarbageEvent_H_
#include "String.h"
using namespace std;
class StackGarbageEvent
{
public:
    char width;
    char height;
    int owner;
    bool skill;
    StackGarbageEvent(char width, char height, int owner, bool skill);
    String* toString();

protected:
private:
};
#endif //__StackGarbageEvent_H_
