#ifndef __GameSituation_H_
#define __GameSituation_H_
using namespace std;
class GameSituation
{
public:
    GameSituation(map<Integer*,PanelSituation*>* panelSituations);
    map<Integer*,PanelSituation*> getPlayerIdToPanelSituation();

protected:
private:
    map<Integer*,PanelSituation*>* playerIdToPanelSituation;
};
#endif //__GameSituation_H_
