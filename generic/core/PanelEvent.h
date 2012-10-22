#ifndef __PanelEvent_H_
#define __PanelEvent_H_

#include <cstdint>
#include "PanelEventType.h"

class PanelEvent {
private:


protected:
public:
  PanelEventType type;
  int32_t data1;
  int32_t data2;
  int32_t data3;
  PanelEvent(PanelEventType type, int32_t data1 = 0, int32_t data2 = 0);
};

#endif //__PanelEvent_H_
