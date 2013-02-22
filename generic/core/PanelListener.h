#ifndef __PanelListener_H_
#define __PanelListener_H_

#include <cstdint>
#include "Combo.h"

class PanelListener {
private:

protected:
public:
  virtual void onCombo(Combo* combo) = 0;
  virtual void onEvent(int64_t playerId, PanelEvent panelEvent) = 0;
  virtual void onGameOver() = 0;

  virtual ~PanelListener() {};
};

#endif //__PanelListener_H_
