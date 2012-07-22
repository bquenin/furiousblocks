#include "Move.h"
using namespace std;

Move::Move(char type)
:type(0)
{
    this->type = type;
}

Move::Move(Move* move)
:type(0)
{
    type = move->type;
}

char Move::getType()
{
    return type;
}

int Move::hashCode()
{
    int prime = 31;
    int result = 1;
    result = (prime * result) + type;
    return result;
}

bool Move::equals(Object* obj)
{
    if (this == obj){
        return true;
    }
    if (obj == nullptr){
        return false;
    }
    if (getClass() != obj->getClass()){
        return false;
    }
    Move* other = TODO CastExpression;
    return type == other->type;
}

String* Move::toString()
{
    StringBuilder* builder = new StringBuilder();
    builder->append(TODO StringLiteral);
    builder->append(type);
    builder->append(TODO StringLiteral);
    return builder->toString();
}
