#include <cstdint>
#include "TimeLag2SkillChainPanel.h"

TimeLag2SkillChainPanel::TimeLag2SkillChainPanel(int32_t seed, int32_t playerId)
{
    scrollingEnabled = false;
    for (int32_t y = 0;y < Panel::Y;y++){
        for (int32_t x = 0;x < Panel::X;x++){
            blocks[x][y] = y == 0 ? newRandom(nullptr) : nullptr;
        }
    }
    blocks[0][1] = newBlock(BlockType::TUTORIAL);
    blocks[1][1] = newBlock(BlockType::TUTORIAL);
    blocks[2][1] = newBlock(BlockType::YELLOW);
    blocks[3][1] = newBlock(BlockType::TUTORIAL);
    blocks[4][1] = newBlock(BlockType::TUTORIAL);
    blocks[5][1] = newBlock(BlockType::TUTORIAL);
    blocks[0][2] = newBlock(BlockType::TUTORIAL);
    blocks[1][2] = newBlock(BlockType::TUTORIAL);
    blocks[2][2] = newBlock(BlockType::YELLOW);
    blocks[3][2] = newBlock(BlockType::RED);
    blocks[4][2] = newBlock(BlockType::YELLOW);
    blocks[5][2] = newBlock(BlockType::TUTORIAL);
    blocks[0][3] = newBlock(BlockType::TUTORIAL);
    blocks[1][3] = newBlock(BlockType::TUTORIAL);
    blocks[2][3] = newBlock(BlockType::GREEN);
    blocks[3][3] = newBlock(BlockType::RED);
    blocks[4][3] = newBlock(BlockType::YELLOW);
    blocks[5][3] = newBlock(BlockType::TUTORIAL);
    blocks[0][4] = newBlock(BlockType::TUTORIAL);
    blocks[1][4] = newBlock(BlockType::TUTORIAL);
    blocks[2][4] = newBlock(BlockType::BLUE);
    blocks[3][4] = newBlock(BlockType::GREEN);
    blocks[4][4] = newBlock(BlockType::BLUE);
    blocks[5][4] = newBlock(BlockType::BLUE);
    blocks[0][5] = newBlock(BlockType::TUTORIAL);
    blocks[1][5] = newBlock(BlockType::TUTORIAL);
    blocks[2][5] = newBlock(BlockType::GREEN);
    blocks[3][5] = newBlock(BlockType::BLUE);
    blocks[4][5] = newBlock(BlockType::YELLOW);
    blocks[5][5] = newBlock(BlockType::TUTORIAL);
    blocks[0][6] = newBlock(BlockType::TUTORIAL);
    blocks[1][6] = newBlock(BlockType::TUTORIAL);
    blocks[2][6] = newBlock(BlockType::GREEN);
    blocks[3][6] = newBlock(BlockType::BLUE);
    blocks[4][6] = newBlock(BlockType::TUTORIAL);
    blocks[5][6] = newBlock(BlockType::TUTORIAL);
    blocks[0][7] = newBlock(BlockType::TUTORIAL);
    blocks[1][7] = newBlock(BlockType::TUTORIAL);
    blocks[2][7] = newBlock(BlockType::YELLOW);
    blocks[3][7] = newBlock(BlockType::RED);
    blocks[4][7] = newBlock(BlockType::TUTORIAL);
    blocks[5][7] = newBlock(BlockType::TUTORIAL);
}
