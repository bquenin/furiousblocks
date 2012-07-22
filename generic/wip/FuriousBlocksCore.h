#ifndef __FuriousBlocksCore_H_
#define __FuriousBlocksCore_H_
#include "panel.h"
#include "FuriousBlocksCoreListener.h"
#include "PanelSituation.h"
#include "SimpleRNG.h"
#include "GameSituation.h"
#include "NetworkContext.h"
using namespace std;
class FuriousBlocksCore
{
public:
    BlockType* initialBlockTypes[FuriousBlocksCoreDefaults::PANEL_WIDTH][FuriousBlocksCoreDefaults::PANEL_HEIGHT];
    FuriousBlocksCore(int seed);
    FuriousBlocksCore(int seed, FuriousBlocksCoreListener* listener);
    void addPlayer(Player* newPlayer);
    void addPlayer(Player* newPlayer, Panel* panel);
    AtomicReference<GameSituation*> getGameSituation();
    void run();
    void pause();
    void resume();
    void stop();
    void onTick(long  tick);
    void onCombo(Combo* combo);
    void onEvent(long  playerId, PanelEvent* panelEvent);
    bool equals(Object* o);
    int hashCode();
    set<Player*> getPlayers();
    void justATick();

protected:
    map<Player*,Panel*>* playerToPanel;
    AtomicReference<GameSituation*>* gameSituation;
    map<Integer*,NetworkContext*>* networkContexts;

private:
    int seed;
    long nanoPeriod;
    long tick;
    bool running;
    bool paused;
    bool singleTick;
    FuriousBlocksCoreListener* listener;
};
#endif //__FuriousBlocksCore_H_
