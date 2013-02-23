//
// Created by bquenin on 2/22/13.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "Garbage.h"
#include "Panel.h"
#include "BlockLine.h"

Garbage::Garbage(Panel& panel, int32_t width, int32_t height, int32_t owner, bool skill)
: BlockBar(panel, width, height, owner)
, skill(skill) {
}

void Garbage::inject(int32_t x, int32_t y) {
  for (int32_t j = y, h = 0; h < height; j--, h++) {
    for (int32_t i = x, w = 0; w < width; i++, w++) {
      panel.blocks[i][j] = panel.newBlock(BlockType::GARBAGE);
      panel.blocks[i][j]->garbageOwner = owner;
      barBlocks.insert(panel.blocks[i][j]);
    }
  }
  panel.garbages.insert(std::shared_ptr<Garbage>(this));
  switch (height) {
    case 1:
      for (int32_t w = 1; w < (width - 1); w++) {
        panel.blocks[x + w][y]->garbageBlockType = GarbageBlockType::UPDOWN;
      }
      panel.blocks[x][y]->garbageBlockType = GarbageBlockType::UPLEFTDOWN;
      panel.blocks[(x + width) - 1][y]->garbageBlockType = GarbageBlockType::UPRIGHTDOWN;
      break;
    default:
      for (int32_t h = 0; h < height; h++) {
        for (int32_t w = 0; w < width; w++) {
          panel.blocks[x + w][y - h]->garbageBlockType = GarbageBlockType::PLAIN;
        }
      }
      panel.blocks[x][y]->garbageBlockType = GarbageBlockType::UPLEFT;
      panel.blocks[x][y - (height - 1)]->garbageBlockType = GarbageBlockType::DOWNLEFT;
      panel.blocks[(x + width) - 1][y]->garbageBlockType = GarbageBlockType::UPRIGHT;
      panel.blocks[(x + width) - 1][y - (height - 1)]->garbageBlockType = GarbageBlockType::DOWNRIGHT;
      if (width > 2) {
        for (int32_t w = 1; w < (width - 1); w++) {
          panel.blocks[x + w][y]->garbageBlockType = GarbageBlockType::UP;
          panel.blocks[x + w][y - (height - 1)]->garbageBlockType = GarbageBlockType::DOWN;
        }
      }
      if (height > 2) {
        for (int32_t h = 1; h < (height - 1); h++) {
          panel.blocks[x][y - h]->garbageBlockType = GarbageBlockType::LEFT;
          panel.blocks[(x + width) - 1][y - h]->garbageBlockType = GarbageBlockType::RIGHT;
        }
      }
      break;
  }
}

void Garbage::blink(std::shared_ptr<Combo> combo) {
  triggeringCombo = combo;
  BlockBar::blink();
}

int32_t Garbage::reveal(int32_t xOrigin, int32_t yOrigin, int32_t revealingTime, Clearing& parentClearing) {
  if (isRevealing()) {
    return revealingTime;
  }

  for (auto garbage = std::next(panel.garbages.begin()); garbage != panel.garbages.end(); ++garbage) {
    if (garbage->get() == this) {
      panel.garbages.erase(garbage);
      break;
    }
  }

  int32_t revealingTimeIncrement = revealingTime;
  if (triggeringCombo != nullptr) {
    for (auto block: triggeringCombo->blocks) {
      if (block->state == BlockState::EXPLODING) {
        break;
      }
      block->explode(revealingTimeIncrement += FuriousBlocksCoreDefaults::BLOCK_REVEALINGTIMEINCREMENT);
    }
  }
  auto subLine = std::make_shared<BlockLine>(panel, width, owner);
  subLine->inject(xOrigin, yOrigin);
  parentClearing.addBlockBar(subLine);
  revealingTimeIncrement = subLine->reveal(xOrigin, yOrigin, revealingTimeIncrement);
  if (height > 1) {
    std::shared_ptr<Garbage> subGarbage (panel.newGarbage(width, height - 1, owner, skill));
    subGarbage->inject(xOrigin, yOrigin + height - 1);
    parentClearing.addBlockBar(subGarbage);
    for (int32_t y = yOrigin + 1; y < yOrigin + height && y < Panel::Y; y++) {
      for (int32_t x = xOrigin; x < xOrigin + width && x < Panel::X; x++) {
        if (y <= Panel::Y_DISPLAY) {
          panel.blocks[x][y]->reveal(revealingTimeIncrement += FuriousBlocksCoreDefaults::BLOCK_REVEALINGTIMEINCREMENT);
        } else {
          panel.blocks[x][y]->reveal(-1);
        }
      }
    }
  }
  return revealingTimeIncrement;
}

void Garbage::onDoneRevealing() {
  for (auto block: barBlocks) {
    block->idle();
  }
}
