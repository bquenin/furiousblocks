#ifndef __PanelEvent_H_
#define __PanelEvent_H_

#include <cstdint>
#include "PanelEventType.h"

class PanelEvent {
private:
  PanelEvent(PanelEventType type, int32_t data1, int32_t data2);

protected:
public:
  PanelEventType type;
  int32_t data1 = 0;
  int32_t data2 = 0;
  int64_t data3 = 0;
  PanelEvent(PanelEventType type);
  PanelEvent(PanelEventType type, int32_t data1);
};

#endif //__PanelEvent_H_
