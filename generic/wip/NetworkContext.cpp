#include "NetworkContext.h"
using namespace std;

NetworkContext::NetworkContext()
:backlog(new HashMap<Long*,TickStatus*>()), garbageEventsBacklog(new HashMap<Long*,LinkedList<StackGarbageEvent*> >()), lastACKedTick(new AtomicLong(-1))
{
}

long NetworkContext::getLastACKedTick()
{
    return lastACKedTick->get();
}

void NetworkContext::setLastACKedTick(long  lastACKedTick)
{
    this->lastACKedTick.set(lastACKedTick);
}

map<Long*,TickStatus*> NetworkContext::getBacklog()
{
    return backlog;
}

map<Long*,LinkedList<StackGarbageEvent*> > NetworkContext::getGarbageEventsBacklog()
{
    return garbageEventsBacklog;
}
