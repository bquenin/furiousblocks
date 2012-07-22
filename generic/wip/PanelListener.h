#ifndef __PanelListener_H_
#define __PanelListener_H_
using namespace std;
class PanelListener
{
public:
    virtual void onCombo(Combo* combo);

protected:
private:
    virtual void onEvent(long  playerId, PanelEvent* panelEvent);
};
#endif //__PanelListener_H_
