#ifndef __FuriousBlocksCoreListener_H_
#define __FuriousBlocksCoreListener_H_

#include <cstdint>
#include "PanelEvent.h"

class FuriousBlocksCoreListener {
public:
  virtual void onEvent(int64_t playerId, PanelEvent *panelEvent);
  virtual ~FuriousBlocksCoreListener();
};

#endif //__FuriousBlocksCoreListener_H_
