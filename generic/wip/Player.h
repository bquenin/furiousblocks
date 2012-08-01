#ifndef __Player_H_
#define __Player_H_

#include <cstdint>
#include <string>
#include "PanelSituation.h"
#include "Move.h"

class Player {
private:
  //    BlockingQueue<PanelSituation*>* situations = new LinkedBlockingQueue<PanelSituation*>();

protected:
  //    AtomicReference<Move*>* move = new AtomicReference<Move*>();
  Player(int32_t id, const std::string name);
  //    virtual void playerTick(PanelSituation* panelSituation, bool isMostRecentData) = 0;

public:
  int32_t id = 0;
  std::string name;
  //    Move* onMoveRequest();
  //    void onSituationUpdate(PanelSituation* panelSituation);
  //    void run();
};

#endif //__Player_H_
