#include <cstdint>
#include <map>
#include <list>
#include "AtomicLong.h"
#include "TickStatus.h"
#include "StackGarbageEvent.h"
#include "NetworkContext.h"

using namespace std;

NetworkContext::NetworkContext() {
}

int64_t NetworkContext::getLastACKedTick() {
  return lastACKedTick.get();
}

void NetworkContext::setLastACKedTick(int64_t lastACKedTick) {
  this->lastACKedTick.set(lastACKedTick);
}

map<int64_t, TickStatus *> NetworkContext::getBacklog() {
  return backlog;
}

map<int64_t, list<StackGarbageEvent *> > NetworkContext::getGarbageEventsBacklog() {
  return garbageEventsBacklog;
}
