#include <cstdint>
#include "PanelEvent.h"

PanelEvent::PanelEvent(PanelEventType type, int32_t data1, int32_t data2)
: type(type)
, data1(data1)
, data2(data2) {
}
