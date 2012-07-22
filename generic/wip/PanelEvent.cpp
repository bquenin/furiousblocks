#include "PanelEvent.h"
using namespace std;

PanelEvent::PanelEvent(PanelEventType type)
:type(nullptr), data1(0), data2(0), data3(0)
{
    PanelEvent(type, 0, 0);
}

PanelEvent::PanelEvent(PanelEventType type, int data1)
:type(nullptr), data1(0), data2(0), data3(0)
{
    PanelEvent(type, data1, 0);
}

PanelEvent::PanelEvent(PanelEventType type, int data1, int data2)
:type(nullptr), data1(0), data2(0), data3(0)
{
    this->type = type;
    this->data1 = data1;
    this->data2 = data2;
}

int PanelEvent::hashCode()
{
    int prime = 31;
    int result = 1;
    result = (prime * result) + data1;
    result = (prime * result) + data2;
    result = (prime * result) + ((type == nullptr) ? 0 : type->hashCode());
    return result;
}

bool PanelEvent::equals(Object* obj)
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
    PanelEvent* other = TODO CastExpression;
    if (data1 != other->data1){
        return false;
    }
    if (data2 != other->data2){
        return false;
    }
    return type == other->type;
}
