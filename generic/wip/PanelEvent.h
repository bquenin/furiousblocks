#ifndef __PanelEvent_H_
#define __PanelEvent_H_
#include "PanelEventType.h"
using namespace std;
class PanelEvent
{
public:
    PanelEventType type;
    int data1;
    int data2;
    long data3;
    PanelEvent(PanelEventType type);
    PanelEvent(PanelEventType type, int data1);
    int hashCode();
    bool equals(Object* obj);

protected:
private:
    PanelEvent(PanelEventType type, int data1, int data2);
};
#endif //__PanelEvent_H_
