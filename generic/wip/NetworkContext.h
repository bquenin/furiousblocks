#ifndef __NetworkContext_H_
#define __NetworkContext_H_

#include <cstdint>
#include <map>
#include <list>
#include "AtomicLong.h"
#include "TickStatus.h"
#include "StackGarbageEvent.h"

using namespace std;

class NetworkContext {
private:
  map<int64_t, TickStatus *> backlog;
  map<int64_t, list<StackGarbageEvent *> > garbageEventsBacklog;
  AtomicLong& lastACKedTick = new AtomicLong(-1);

protected:
public:
  NetworkContext();
  int64_t getLastACKedTick();
  void setLastACKedTick(int64_t lastACKedTick);
  map<int64_t, TickStatus *> getBacklog();
  map<int64_t, list<StackGarbageEvent *> > getGarbageEventsBacklog();
};

#endif //__NetworkContext_H_
