#ifndef __PanelListener_H_
#define __PanelListener_H_

#include <cstdint>
#include "Combo.h"

class PanelListener {
private:

protected:
public:
  virtual void onCombo(Combo *combo);
  virtual void onEvent(int64_t playerId, PanelEvent *panelEvent);
};

#endif //__PanelListener_H_
