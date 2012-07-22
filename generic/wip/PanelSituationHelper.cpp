#include "PanelSituationHelper.h"
using namespace std;

PanelSituationHelper::PanelSituationHelper(PanelSituation* panelSituation)
:panelSituation(nullptr), blockSituations(nullptr)
{
    this->panelSituation = panelSituation;
    blockSituations = panelSituation->getBlockSituations();
}

PanelSituation* PanelSituationHelper::getPanelSituation()
{
    return panelSituation;
}

int PanelSituationHelper::getHeight()
{
    for (int j = blockSituations[0]->length - 1;j >= 0;j--){
        for (auto **&blockSituation: blockSituations){
            if (blockSituation[j] != nullptr){
                return j;
            }
        }
    }
    return 0;
}

bool PanelSituationHelper::isBlockSwitchPossible(Point* location)
{
    return BlockSituation->isMovable(blockSituations[location->x][location->y]) && BlockSituation->isMovable(blockSituations[location->x + 1][location->y]);
}

bool PanelSituationHelper::isAnyBlockSwitching()
{
    for (int j = 0;j < blockSituations[0]->length;j++){
        for (auto **&blockSituation: blockSituations){
            if (blockSituation[j] == nullptr){
                continue;
            }
            BlockState state = blockSituation[j].getState();
            if ((state == BlockState::SWITCHING_FORTH) || (state == BlockState::SWITCHING_BACK)){
                return true;
            }
        }
    }
    return false;
}

bool PanelSituationHelper::isAnyBlockFallingOrHoveringOrAirBouncing()
{
    for (int j = 1;j < blockSituations[0]->length;j++){
        for (auto **&blockSituation: blockSituations){
            if (blockSituation[j] == nullptr){
                continue;
            }
            BlockState state = blockSituation[j].getState();
            if (state == BlockState::AIRBOUNCING || state == BlockState::DONE_AIRBOUNCING || state == BlockState::HOVERING || state == BlockState::FALLING){
                return true;
            }
        }
    }
    return false;
}

bool PanelSituationHelper::isClearingGarbage()
{
    return panelSituation->isClearing();
}

bool PanelSituationHelper::blockSwitchAndDetectFalling(int x, int y)
{
    BlockSituation* src = blockSituations[x][y];
    BlockSituation* dst = blockSituations[x + 1][y];
    if ((src == nullptr) && (dst == nullptr)){
        return true;
    }
    if (src != nullptr){
        if (!BlockSituation->isComputable(src)){
            return false;
        }
    }
    if (dst != nullptr){
        if (!BlockSituation->isComputable(dst)){
            return false;
        }
    }
    blockSituations[x][y] = blockSituations[x + 1][y];
    blockSituations[x + 1][y] = src;
    if ((y - 1) >= 0){
        if (blockSituations[x][y - 1] == nullptr){
            return false;
        }
        if (blockSituations[x + 1][y - 1] == nullptr){
            return false;
        }
    }
    return true;
}

bool PanelSituationHelper::detectCombo()
{
    for (int y = 1;y < blockSituations[0]->length;y++){
        for (int x = 0;x < blockSituations->length;x++){
            BlockSituation* current = blockSituations[x][y];
            if (current == nullptr || current->getState() != BlockState::IDLE || !current->getType()->movable || !current->getType()->combinable){
                continue;
            }
            int xidem = 1;
            for (int right = x + 1;right < blockSituations->length;right++){
                BlockSituation* rightBlock = blockSituations[right][y];
                if (rightBlock == nullptr || rightBlock->getState() != BlockState::IDLE || rightBlock->getType() != current->getType()){
                    break;
                }
                xidem++;
            }
            if (xidem >= 3){
                return true;
            }
            int yidem = 1;
            for (int above = y + 1;above < blockSituations[0]->length;above++){
                BlockSituation* aboveBlock = blockSituations[x][above];
                if (aboveBlock == nullptr || aboveBlock->getState() != BlockState::IDLE || aboveBlock->getType() != current->getType()){
                    break;
                }
                yidem++;
            }
            if (yidem >= 3){
                return true;
            }
        }
    }
    return false;
}

int PanelSituationHelper::isGarbaged()
{
    for (int j = 1;j < blockSituations[0]->length;j++){
        for (auto **&blockSituation: blockSituations){
            if (blockSituation[j] == nullptr){
                continue;
            }
            if ((blockSituation[j].getType() == BlockType::GARBAGE) && (blockSituation[j].getState() == BlockState::IDLE)){
                return j;
            }
        }
    }
    return -1;
}

bool PanelSituationHelper::isLineEmpty(int line)
{
    for (auto **&blockSituation: blockSituations){
        if (blockSituation[line] != nullptr){
            return false;
        }
    }
    return true;
}
