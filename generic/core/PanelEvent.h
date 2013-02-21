#ifndef __PanelEvent_H_
#define __PanelEvent_H_

#include <cstdint>
#include "PanelEventType.h"

class PanelEvent {
private:


protected:
public:
  PanelEventType type;
  PanelEvent(PanelEventType type);
};

#endif //__PanelEvent_H_
