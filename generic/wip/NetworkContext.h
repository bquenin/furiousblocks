#ifndef __NetworkContext_H_
#define __NetworkContext_H_
#include "AtomicLong.h"
#include "StackGarbageEvent.h"
using namespace std;
class NetworkContext
{
public:
    NetworkContext();
    long getLastACKedTick();
    void setLastACKedTick(long  lastACKedTick);
    map<Long*,TickStatus*> getBacklog();
    map<Long*,LinkedList<StackGarbageEvent*> > getGarbageEventsBacklog();

protected:
private:
    map<Long*,TickStatus*>* backlog;
    map<Long*,LinkedList<StackGarbageEvent*> >* garbageEventsBacklog;
    AtomicLong* lastACKedTick;
};
#endif //__NetworkContext_H_
