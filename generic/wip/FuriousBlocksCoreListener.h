#ifndef __FuriousBlocksCoreListener_H_
#define __FuriousBlocksCoreListener_H_

#include <cstdint>
#include "PanelEvent.h"

class FuriousBlocksCoreListener {
private:

protected:
public:
  virtual void onEvent(int64_t playerId, PanelEvent *panelEvent);
};

#endif //__FuriousBlocksCoreListener_H_
