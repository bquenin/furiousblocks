#ifndef __FuriousBlocksCoreListener_H_
#define __FuriousBlocksCoreListener_H_

#include <cstdint>
#include "Combo.h"

class FuriousBlocksCoreListener {
public:
  virtual void onCombo(Combo *combo) = 0;
//  virtual void onEvent(int64_t playerId, PanelEvent panelEvent) = 0;
  virtual void onGameOver() = 0;
  virtual ~FuriousBlocksCoreListener() {};

};

#endif //__FuriousBlocksCoreListener_H_
