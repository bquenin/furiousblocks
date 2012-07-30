#ifndef __Player_H_
#define __Player_H_

#include <cstdint>
#include <string>
#include "Move.h"

using namespace std;

class Player {
private:
  //    static const SimpleRNG& RANDOM = new SimpleRNG(static_cast<int32_t>(System::nanoTime()));
  //    BlockingQueue<PanelSituation*>& situations = new LinkedBlockingQueue<PanelSituation*>();

protected:
  //    AtomicReference<Move*>& move = new AtomicReference<Move*>();
  Player(int32_t id, string& name);
  Player(string& name);
  virtual void playerTick(PanelSituation& panelSituation, bool isMostRecentData) = 0;

public:
  int32_t id = 0;
  string name;
  int32_t getId();
  string &getName();
  Move& onMoveRequest();
  void onSituationUpdate(PanelSituation& panelSituation);
  void run();
};

#endif //__Player_H_
