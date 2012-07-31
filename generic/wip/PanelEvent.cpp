#include <cstdint>
#include "PanelEvent.h"

PanelEvent::PanelEvent(PanelEventType type)
{
    PanelEvent(type, 0, 0);
}

PanelEvent::PanelEvent(PanelEventType type, int32_t data1)
{
    PanelEvent(type, data1, 0);
}

PanelEvent::PanelEvent(PanelEventType type, int32_t data1, int32_t data2)
{
    this->type = type;
    this->data1 = data1;
    this->data2 = data2;
}
