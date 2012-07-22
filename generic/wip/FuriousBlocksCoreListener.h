#ifndef __FuriousBlocksCoreListener_H_
#define __FuriousBlocksCoreListener_H_
#include "PanelEvent.h"
using namespace std;
class FuriousBlocksCoreListener
{
public:
protected:
private:
    virtual void onEvent(long  playerId, PanelEvent* panelEvent);
};
#endif //__FuriousBlocksCoreListener_H_
