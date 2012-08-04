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
  //    virtual void playerTick(PanelSituation* panelSituation, bool isMostRecentData) = 0;

public:
  Player(int32_t id = 123, const std::string name = "default");
  int32_t id;
  std::string name;
  //    Move* onMoveRequest();
  //    void onSituationUpdate(PanelSituation* panelSituation);
  //    void run();
  void onSituationUpdate(PanelSituation *panelSituation);
};

#endif //__Player_H_
