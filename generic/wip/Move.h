#ifndef __Move_H_
#define __Move_H_
#include "String.h"
using namespace std;
class Move
{
public:
    Move(char type);
    Move(Move* move);
    char getType();
    int hashCode();
    bool equals(Object* obj);
    String* toString();

protected:
private:
    char type;
};
#endif //__Move_H_
