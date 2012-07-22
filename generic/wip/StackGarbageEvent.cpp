#include "StackGarbageEvent.h"
using namespace std;

StackGarbageEvent::StackGarbageEvent(char width, char height, int owner, bool skill)
:width(0), height(0), owner(0), skill(false)
{
    this->width = width;
    this->height = height;
    this->owner = owner;
    this->skill = skill;
}

String* StackGarbageEvent::toString()
{
    StringBuilder* builder = new StringBuilder();
    builder->append(TODO StringLiteral);
    builder->append(width);
    builder->append(TODO StringLiteral);
    builder->append(height);
    builder->append(TODO StringLiteral);
    builder->append(owner);
    builder->append(TODO StringLiteral);
    builder->append(skill);
    builder->append(TODO StringLiteral);
    return builder->toString();
}
