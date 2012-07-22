#ifndef __Point_H_
#define __Point_H_
#include "String.h"
using namespace std;
class Point
{
public:
    int x;
    int y;
    Point();
    Point(Point* p);
    Point(int x, int y);
    bool equals(Object* obj);
    String* toString();

protected:
private:
};
#endif //__Point_H_
