#ifndef __Player_H_
#define __Player_H_
#include "PanelSituation.h"
#include "String.h"
#include "SimpleRNG.h"
#include "Move.h"
using namespace std;
class Player
{
public:
    int id;
    String* name;
    int getId();
    String* getName();
    Move* onMoveRequest();
    void onSituationUpdate(PanelSituation* panelSituation);
    void run();
    int hashCode();
    bool equals(Object* obj);

protected:
    AtomicReference<Move*>* move;
    Player(int id, String* name);
    Player(String* name);
    virtual void playerTick(PanelSituation* panelSituation, bool isMostRecentData) = 0;

private:
    static const SimpleRNG* RANDOM = new SimpleRNG(TODO CastExpression);
    BlockingQueue<PanelSituation*>* situations;
};
#endif //__Player_H_
