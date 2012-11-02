#include <cstdint>
#include "X2Chain1ChainsPanel.h"

X2Chain1ChainsPanel::X2Chain1ChainsPanel(int32_t seed, int32_t playerId)
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
    blocks[1][2] = newBlock(BlockType::RED);
    blocks[2][2] = newBlock(BlockType::RED);
    blocks[3][2] = newBlock(BlockType::TUTORIAL);
    blocks[4][2] = newBlock(BlockType::RED);
    blocks[5][2] = newBlock(BlockType::TUTORIAL);
    blocks[0][3] = nullptr;
    blocks[1][3] = nullptr;
    blocks[2][3] = newBlock(BlockType::YELLOW);
    blocks[3][3] = nullptr;
    blocks[4][3] = nullptr;
    blocks[5][3] = nullptr;
    blocks[0][4] = nullptr;
    blocks[1][4] = nullptr;
    blocks[2][4] = newBlock(BlockType::YELLOW);
    blocks[3][4] = nullptr;
    blocks[4][4] = nullptr;
    blocks[5][4] = nullptr;
}
