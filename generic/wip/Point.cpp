#include "Point.h"
using namespace std;

Point::Point()
:x(0), y(0)
{
    Point(0, 0);
}

Point::Point(Point* p)
:x(0), y(0)
{
    Point(p->x, p->y);
}

Point::Point(int x, int y)
:x(0), y(0)
{
    this->x = x;
    this->y = y;
}

bool Point::equals(Object* obj)
{
    if (TODO InstanceofExpression){
        Point* pt = TODO CastExpression;
        return (x == pt->x) && (y == pt->y);
    }
    return TODO SuperMethodInvocation;
}

String* Point::toString()
{
    return getClass().getName() + TODO StringLiteral;
}
