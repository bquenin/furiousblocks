#include "PanelSituation.h"
using namespace std;

PanelSituation::PanelSituation(BlockSituation*** blockSituations, bool isLocked, Collection<ComboSituation*>* comboSituations, Point* cursorPosition, int scrollingOffset, PanelState state, int stateTick, Collection<GarbageSituation*>* garbageSituations, Collection<GarbageSituation*>* garbageStackSituation, int skillChainLevel, int freezingTime, bool gameOver, int wallOffset, bool gracing, int score, bool clearing)
:isLocked(false), comboSituations(nullptr), cursorPosition(nullptr), scrollingOffset(0), state(nullptr), stateTick(0), garbageSituations(nullptr), garbageStackSituation(nullptr), skillChainLevel(0), freezingTime(0), gameOver(false), wallOffset(0), gracing(false), score(0), clearing(false)
{
    this->blockSituations = blockSituations;
    this->isLocked = isLocked;
    this->comboSituations = comboSituations;
    this->state = state;
    this->stateTick = stateTick;
    this->garbageSituations = garbageSituations;
    this->garbageStackSituation = garbageStackSituation;
    this->skillChainLevel = skillChainLevel;
    this->cursorPosition = cursorPosition;
    this->scrollingOffset = scrollingOffset;
    this->freezingTime = freezingTime;
    this->gameOver = gameOver;
    this->wallOffset = wallOffset;
    this->gracing = gracing;
    this->score = score;
    this->clearing = clearing;
}

BlockSituation* PanelSituation::getBlockSituations()
{
    return blockSituations;
}

bool PanelSituation::isLocked()
{
    return isLocked;
}

Collection<ComboSituation*> PanelSituation::getComboSituations()
{
    return Collections->unmodifiableCollection(comboSituations);
}

Point* PanelSituation::getCursorPosition()
{
    return cursorPosition;
}

int PanelSituation::getScrollingOffset()
{
    return scrollingOffset;
}

PanelState PanelSituation::getState()
{
    return state;
}

int PanelSituation::getStateTick()
{
    return stateTick;
}

int PanelSituation::getSkillChainLevel()
{
    return skillChainLevel;
}

int PanelSituation::getFreezingTime()
{
    return freezingTime;
}

bool PanelSituation::isGameOver()
{
    return gameOver;
}

int PanelSituation::getWallOffset()
{
    return wallOffset;
}

bool PanelSituation::isGracing()
{
    return gracing;
}

int PanelSituation::getScore()
{
    return score;
}

GarbageSituation* PanelSituation::getGarbageByBlock(int blockId)
{
    for (auto *&garbageSituation: garbageSituations){
        if (garbageSituation->contains(blockId)){
            return garbageSituation;
        }
    }
    return nullptr;
}

ComboSituation* PanelSituation::getComboByBlock(int blockId)
{
    for (auto *&comboSituation: comboSituations){
        if (comboSituation->contains(blockId)){
            return comboSituation;
        }
    }
    return nullptr;
}

PanelSituation* PanelSituation::getSimpleClone()
{
    BlockSituation* copy[blockSituations->length][blockSituations[0]->length];
    for (int i = 0;i < copy->length;i++){
        System->arraycopy(blockSituations[i], 0, copy[i], 0, copy[i]->length);
    }
    return new PanelSituation(copy, isLocked, comboSituations, cursorPosition, scrollingOffset, state, stateTick, garbageSituations, garbageStackSituation, skillChainLevel, freezingTime, gameOver, wallOffset, gracing, score, clearing);
}

bool PanelSituation::isClearing()
{
    return clearing;
}

bool PanelSituation::equals(Object* o)
{
    if (this == o){
        return true;
    }
    if (o == nullptr || getClass() != o->getClass()){
        return false;
    }
    PanelSituation* that = TODO CastExpression;
    return blockSituations->hashCode() == that->blockSituations.hashCode();
}

int PanelSituation::hashCode()
{
    if (blockSituations == nullptr){
        return 0;
    }
    int result = 1;
    for (int x = 0;x < FuriousBlocksCoreDefaults::PANEL_WIDTH;x++){
        for (int y = 0;y < FuriousBlocksCoreDefaults::PANEL_HEIGHT + 1;y++){
            result = 31 * result + (blockSituations[x][y] == nullptr ? 0 : blockSituations[x][y].getId());
        }
    }
    result = 31 * result + scrollingOffset;
    return result;
}
