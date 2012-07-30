#ifndef __PanelListener_H_
#define __PanelListener_H_

#include <cstdint>
#include "Combo.h"
#include "PanelEvent.h"

using namespace std;

class PanelListener {
  friend class Panel;
private:
  virtual void onEvent(int64_t playerId, const PanelEvent* panelEvent);
  virtual ~PanelListener();
protected:
public:
  virtual void onCombo(Combo& combo);
};

#endif //__PanelListener_H_
