#include <cassert>
#include <cstdint>
#include <iostream>
#include "Panel.h"
#include "Garbage.h"

Panel::Panel(int32_t seed, int32_t playerId, std::array<std::array<BlockType, FuriousBlocksCoreDefaults::PANEL_HEIGHT>, FuriousBlocksCoreDefaults::PANEL_WIDTH> initialBlockTypes, PanelListener &panelListener)
: lastIndex(-1)
, random(SimpleRNG(seed))
, localTick(0)
, playerId(playerId)
, cursor((Panel::X / 2) - 1, (Panel::Y_DISPLAY / 2))
, levelScrollingSpeed(Panel::INITIAL_SCROLLING_SPEED)
, scrollingSpeed(Panel::INITIAL_SCROLLING_SPEED)
, scrollingDelta(0)
, freezingTime(0)
, bonusFreezingTime(0)
, skillChainLevel(1)
, move(nullptr)
, locked(false)
, lifting(false)
, gracing(false)
, gameOver(false)
, score(0)
, panelListener(panelListener)
, scrollingEnabled(true)
, level(0) {
  for (int32_t y = 0; y < Panel::Y; y++) {
    for (int32_t x = 0; x < Panel::X; x++) {
      blocks[x][y] = nullptr;
    }
  }

  for (int32_t y = 1; y < FuriousBlocksCoreDefaults::PANEL_HEIGHT; y++) {
    for (int32_t x = 0; x < FuriousBlocksCoreDefaults::PANEL_WIDTH; x++) {
      blocks[x][y] = initialBlockTypes[x][y] == static_cast<BlockType>(-1) ? nullptr : newBlock(initialBlockTypes[x][y]);
    }
  }

  for (int32_t x = 0; x < Panel::X; x++) {
    blocks[x][0] = blocks[x][1] == nullptr ? newRandom() : newRandom(blocks[x][1]->type);
  }
}

void Panel::reset() {
  freezingTime = 0;
  bonusFreezingTime = 0;
  skillChainLevel = 1;
  move = nullptr;
  locked = false;
  lifting = false;
  gracing = false;
  gameOver = false;
  combos.clear();
  garbages.clear();
  clearings.clear();
  garbageStack.clear();
  for (int32_t y = 0; y < Panel::Y; y++) {
    for (int32_t x = 0; x < Panel::X; x++) {
      blocks[x][y] = nullptr;
    }
  }
}

void Panel::setTransposedBlocks(std::vector<std::vector<BlockType>> & blockTypes) {
  for (int32_t y = 0; y < blockTypes[0].size(); y++) {
    for (int32_t x = 0; x < blockTypes.size(); x++) {
      blocks[y][x] = blockTypes[x][y] == static_cast<BlockType>(-1) ? nullptr : newBlock(blockTypes[x][y]);
    }
  }
  for (int32_t x = 0; x < Panel::X; x++) {
    blocks[x][0] = blocks[x][1] == nullptr ? newRandom(static_cast<BlockType>(-1)) : newRandom(blocks[x][1]->type);
  }
}

std::unique_ptr<fb::Block> Panel::newRandom(BlockType excludedType) {
  int32_t randomIndex = random.nextInt() % Panel::numberOfRegularBlocks;
  int32_t index = randomIndex == lastIndex ? (randomIndex + 1) % Panel::numberOfRegularBlocks : randomIndex;
  if (index == static_cast<int32_t>(excludedType)) {
    index = (index + 1) % Panel::numberOfRegularBlocks;
  }
  return newBlock(static_cast<BlockType>(lastIndex = index));
}

std::unique_ptr<fb::Block> Panel::newBlock(BlockType blockType) {
  return std::unique_ptr<fb::Block>(new fb::Block(random.nextInt(), blockType));
}

void Panel::onTick(int64_t tick) {
  processMove();
  mechanics(tick);
  std::shared_ptr<Combo> currentCombo(detectCombo());
  if (currentCombo->size() > 0) {
    processCombo(currentCombo);
  }
//  else {
//    currentCombo.reset();
//  }
  scrolling(tick);
  dropGarbages();
}

void Panel::processMove() {
  if (move == nullptr) {
    return;
  }
  MoveType type = move->type;
  switch (type) {
    case MoveType::BLOCK_SWITCH: {
      auto& src = blocks[cursor.x][cursor.y];
      auto& dst = blocks[cursor.x + 1][cursor.y];
      auto& aboveSrc = blocks[cursor.x][cursor.y + 1];
      auto& aboveDst = blocks[cursor.x + 1][cursor.y + 1];
      if (!src && !dst) {
        break;
      }
      if (src != nullptr) {
        if (!fb::Block::isComputable(src.get())) {
          break;
        }
      }
      if (dst != nullptr) {
        if (!fb::Block::isComputable(dst.get())) {
          break;
        }
      }
      if (!dst && aboveDst) {
        if ((aboveDst->state == BlockState::SWITCHING_BACK) || (aboveDst->state == BlockState::SWITCHING_FORTH)) {
          break;
        }
      }
      if (!src && aboveSrc) {
        if ((aboveSrc->state == BlockState::SWITCHING_BACK) || (aboveSrc->state == BlockState::SWITCHING_FORTH)) {
          break;
        }
      }
      if (!src) {
        src = newBlock(BlockType::INVISIBLE);
      }
      if (!dst) {
        dst = newBlock(BlockType::INVISIBLE);
      }
      src->switchForth();
      dst->switchBack();
      panelListener.onEvent(playerId, PanelEvent(PanelEventType::CURSOR_SWAP));
    }
      break;
    case MoveType::CURSOR_DOWN:
      if (cursor.y != 1) {
        cursor.y--;
        panelListener.onEvent(playerId, PanelEvent(PanelEventType::CURSOR_MOVE));
      }
      break;
    case MoveType::CURSOR_LEFT:
      if (cursor.x != 0) {
        cursor.x--;
        panelListener.onEvent(playerId, PanelEvent(PanelEventType::CURSOR_MOVE));
      }
      break;
    case MoveType::CURSOR_RIGHT:
      if (cursor.x != (Panel::X - 2)) {
        cursor.x++;
        panelListener.onEvent(playerId, PanelEvent(PanelEventType::CURSOR_MOVE));
      }
      break;
    case MoveType::CURSOR_UP:
      if (cursor.y != (gracing ? Panel::Y_DISPLAY : Panel::Y_DISPLAY - 1)) {
        cursor.y++;
        panelListener.onEvent(playerId, PanelEvent(PanelEventType::CURSOR_MOVE));
      }
      break;
    case MoveType::LIFT:
      freeze(0);
      if (!lifting && !locked) {
        lifting = true;
        skillChainLevel = 1;
      }
      break;
  }
  move.reset(nullptr);
}

void Panel::dropGarbages() {
  std::unordered_set<Garbage*> duplicata(garbageStack);
  for (auto garbage : duplicata) {
    int32_t y = (Panel::Y_DISPLAY + garbage->height) - 1;
    for (int32_t h = 0, j = y; h < garbage->height; h++, j--) {
      for (int32_t i = 0, w = 0; w < garbage->width; i++, w++) {
        if (blocks[i][j] != nullptr) {
          return;
        }
      }
    }
    garbageStack.erase(garbage);
    int32_t xPos = garbage->width < Panel::X ? random.nextInt() % (Panel::X - garbage->width) : 0;
    garbage->inject(xPos, y);
  }
}

void Panel::scrolling(int64_t tick) {
  if (((tick % Panel::NEXT_LEVEL) == 0) && (levelScrollingSpeed > 1)) {
    levelScrollingSpeed--;
    level++;
  }
  if (locked) {
    return;
  }
  if (freezingTime > 0) {
    freezingTime--;
    return;
  }
  gracePeriod();
  if (gracing) {
    return;
  }
  scrollingSpeed = lifting ? 1 : scrollingEnabled ? levelScrollingSpeed : INT64_MAX;
  bool needNewLine = false;
  if (tick % scrollingSpeed == 0) {
    scrollingDelta++;
    if (scrollingDelta >= FuriousBlocksCoreDefaults::BLOCK_LOGICALHEIGHT) {
      needNewLine = true;
    }
    scrollingDelta %= FuriousBlocksCoreDefaults::BLOCK_LOGICALHEIGHT;
  }
  if (needNewLine) {
    newLine();
    gracePeriod();
    if (cursor.y != (gracing ? Y_DISPLAY : Y_DISPLAY - 1)) {
      cursor.y++;
    }
  }
}

void Panel::gracePeriod() {
  bool topLineEmpty = true;

  for (int32_t x = 0; x < X; x++) {
    if (blocks[x][Y_DISPLAY]) {
      topLineEmpty = false;
      break;
    }
  }
  if (!topLineEmpty) {
    if (gracing) {
      garbageStack.clear();
      gameOver = true;
      panelListener.onGameOver();
    } else {
      lifting = false;
      gracing = true;
      freeze(FuriousBlocksCoreDefaults::CORE_FREQUENCY * 2);
    }
    return;
  }
  gracing = false;
}

void Panel::freeze(int32_t freezingTime) {
  this->freezingTime = freezingTime;
}

void Panel::newLine() {
  if (lifting) {
    freeze(FuriousBlocksCoreDefaults::CORE_FREQUENCY);
    scrollingDelta = 0;
  }
  lifting = false;
  for (int32_t y = Y - 1; y > 0; y--) {
    for (int32_t x = 0; x < X; x++) {
      blocks[x][y] = std::move(blocks[x][y - 1]);
    }
  }
  for (int32_t x = 0; x < X; x++) {
    blocks[x][0] = blocks[x][1] == nullptr ? newRandom() : newRandom(blocks[x][1]->type);
  }
}

void Panel::stackGarbage(Garbage* garbage) {
  //  if (garbage->isSkill()) {
  //    for (ListIterator<Panel::Garbage *> *iterator = garbageStack->listIterator(garbageStack->size()); iterator->hasPrevious();) {
  //      Panel::Garbage *stackedGarbage = iterator->previous();
  //      if (stackedGarbage->isSkill() && stackedGarbage->height == garbage->height - 1 && stackedGarbage->getOwner() == garbage->getOwner()) {
  //        iterator->set(garbage);
  //        return;
  //      }
  //    }
  //  }
  //  garbageStack->add(garbage);
}

void Panel::mechanics(int64_t tick) {
  locked = false;
  int32_t revealingTime = FuriousBlocksCoreDefaults::BLOCK_REVEALINGTIMEBASE;
  for (int32_t y = 1; y < Panel::Y; y++) {
    for (int32_t x = 0; x < Panel::X; x++) {
      auto& current = blocks[x][y];
      if (!current) {
        continue;
      }

      if (current->justLand) {
        current->justLand = false;
        current->fallingFromClearing = false;
      }

      auto event = current->update();
      if (event) {
        panelListener.onEvent(playerId, *event);
      }

      BlockType type = current->type;
      BlockState state = current->state;
      switch (state) {
        case BlockState::DONE_SWITCHING_FORTH:
          std::swap(blocks[x][y], blocks[x + 1][y]);
          blocks[x][y]->idle();
          blocks[x + 1][y]->idle();
          if (blocks[x][y]->type == BlockType::INVISIBLE) {
            blocks[x][y]->toDelete();
          }
          if (blocks[x + 1][y]->type == BlockType::INVISIBLE) {
            blocks[x + 1][y]->toDelete();
          }
          break;
        case BlockState::TO_DELETE:
          if (type != BlockType::INVISIBLE) {
            for (int32_t k = y + 1; k < Panel::Y; k++) {
              if (!fb::Block::isComputable(blocks[x][k].get())) {
                break;
              }
              blocks[x][k]->fallingFromClearing = true;
            }
          }
          blocks[x][y].reset();
          break;
        case BlockState::IDLE:
          switch (type) {
            case BlockType::BLUE:
            case BlockType::GREEN:
            case BlockType::PURPLE:
            case BlockType::RED:
            case BlockType::YELLOW:
            case BlockType::TUTORIAL:
              if (blocks[x][y - 1] == nullptr) {
                current->hover();
              }
              break;
            case BlockType::GARBAGE: {
              auto garbage = getGarbageByBlock(current);
              if (garbage->hasToFall(x, y)) {
                garbage->fall(x, y);
              }
              x += garbage->width - 1;
            }
              break;
            case BlockType::INVISIBLE:
              break;
          }
          break;
        case BlockState::HOVERING:
          break;
        case BlockState::DONE_AIRBOUNCING:
        case BlockState::DONE_HOVERING:
          if (blocks[x][y - 1] == nullptr) {
            for (int32_t k = y + 1; k < Panel::Y; k++) {
              if (blocks[x][k] == nullptr || !blocks[x][k]->movable || blocks[x][k]->type == BlockType::GARBAGE || blocks[x][k]->state != BlockState::IDLE) {
                break;
              }
              blocks[x][k]->fall();
            }
            std::swap(blocks[x][y - 1], blocks[x][y]);
          } else {
            current->land();
          }
          break;
        case BlockState::FALLING:
          switch (type) {
            case BlockType::BLUE:
            case BlockType::GREEN:
            case BlockType::PURPLE:
            case BlockType::RED:
            case BlockType::YELLOW:
            case BlockType::TUTORIAL:
              if (blocks[x][y - 1] == nullptr) {
                std::swap(blocks[x][y], blocks[x][y - 1]);
              } else {
                current->land();
              }
              break;
            case BlockType::GARBAGE: {
              auto garbage = getGarbageByBlock(current);
              if (garbage->hasToFall(x, y)) {
                garbage->fall(x, y);
              } else {
                garbage->idle();
                // TODO: Send quake event here.
              }
              x += garbage->width - 1;
            }
              break;
            case BlockType::INVISIBLE:
              break;
          }
          break;
        case BlockState::DONE_BLINKING:
          switch (type) {
            case BlockType::BLUE:
            case BlockType::GREEN:
            case BlockType::PURPLE:
            case BlockType::RED:
            case BlockType::YELLOW: {
              auto combo = getComboByBlock(current.get());
              assert(combo);
              for (auto block : combo->blocks) {
                if (block->state == BlockState::EXPLODING) {
                  break;
                }
                block->explode(revealingTime += FuriousBlocksCoreDefaults::BLOCK_REVEALINGTIMEINCREMENT);
              }
            }
              break;
            case BlockType::GARBAGE: {
              auto clearing = getClearingByBlock(current);
              auto garbage = getGarbageByBlock(current);
              revealingTime = garbage->reveal(x, y, revealingTime, *clearing);
              clearing->setRevealingTime(tick + revealingTime);
              clearing->removeBar(garbage);
              x += garbage->width - 1;
            }
              break;
            case BlockType::INVISIBLE:
            case BlockType::TUTORIAL:
              break;
          }
          break;
        case BlockState::DONE_EXPLODING:
          switch (type) {
            case BlockType::BLUE:
            case BlockType::GREEN:
            case BlockType::PURPLE:
            case BlockType::RED:
            case BlockType::YELLOW: {
              auto combo = getComboByBlock(current.get());
              assert(combo);
              bool doneExploding = true;
              for (auto block : combo->blocks) {
                if (block->state != BlockState::DONE_EXPLODING) {
                  doneExploding = false;
                  break;
                }
              }
              if (doneExploding) {
                combos.erase(combo);
                for (auto block: combo->blocks) {
                  block->toDelete();
                }
                combo->blocks.clear();
                combo.reset();
              }
            }
              break;
            case BlockType::GARBAGE:
            case BlockType::INVISIBLE:
            case BlockType::TUTORIAL:
              break;
          }
          break;
        case BlockState::DONE_REVEALING: {
          auto clearing = getClearingByBlock(current);
          if (clearing->isDoneRevealing(tick)) {
            clearing->onDoneRevealing();
            clearings.erase(clearing);
            clearing.reset();
          }
        }
          break;
        case BlockState::EXPLODING:
        case BlockState::BLINKING:
        case BlockState::REVEALING:
        case BlockState::AIRBOUNCING:
          locked = true;
          break;
        case BlockState::SWITCHING_BACK:
        case BlockState::SWITCHING_FORTH:
        default:
          break;
      }
    }
  }
}

std::shared_ptr<Combo> Panel::getComboByBlock(fb::Block* block) {
  for (auto combo: combos) {
    if (combo->contains(block)) {
      return combo;
    }
  }
  return nullptr;
}

std::shared_ptr<Garbage> Panel::getGarbageByBlock(std::shared_ptr<fb::Block> block) {
  for (auto &garbage: garbages) {
    if (garbage->contains(block)) {
      return garbage;
    }
  }
  return nullptr;
}

std::shared_ptr<Clearing> Panel::getClearingByBlock(std::shared_ptr<fb::Block> block) {
  for (auto &clearing: clearings) {
    if (clearing->contains(block)) {
      return clearing;
    }
  }
  return nullptr;
}


std::shared_ptr<Combo> Panel::detectCombo() {
  // Create a new combo
  auto combo = std::make_shared<Combo>(playerId);

  // This creates a boolean mask initialized to false
  std::array<std::array<bool, Panel::Y>, Panel::X> comboMask = {};

  for (int32_t y = 1; y < Panel::Y; y++) {
    for (int32_t x = 0; x < Panel::X; x++) {
      auto& current = blocks[x][y];
      if (current == nullptr || current->state != BlockState::IDLE || !current->movable || !current->combinable) {
        continue;
      }
      int32_t xIdem = 1;
      for (int32_t right = x + 1; right < Panel::X; right++) {
        auto& rightBlock = blocks[right][y];
        if (rightBlock == nullptr || rightBlock->state != BlockState::IDLE || rightBlock->type != current->type) {
          break;
        }
        xIdem++;
      }
      int32_t yIdem = 1;
      for (int32_t above = y + 1; above < Panel::Y; above++) {
        auto& aboveBlock = blocks[x][above];
        if (aboveBlock == nullptr || aboveBlock->state != BlockState::IDLE || aboveBlock->type != current->type) {
          break;
        }
        yIdem++;
      }
      if (xIdem >= 3) {
        for (int32_t k = x; k < (x + xIdem); k++) {
          comboMask[k][y] = true;
        }
      }
      if (yIdem >= 3) {
        for (int32_t k = y; k < (y + yIdem); k++) {
          comboMask[x][k] = true;
        }
      }
    }
  }

  bool originSet = false;
  for (int32_t y = Panel::Y - 1; y > 0; y--) {
    for (int32_t x = 0; x < Panel::X; x++) {
      if (!comboMask[x][y]) {
        continue;
      }
      if (!originSet) {
        combo->x = x;
        combo->y = y;
        originSet = true;
      }
      combo->addBlock(blocks[x][y]);
//      blocks[x][y]->combo = true;
    }
  }
  return std::move(combo);
}

void Panel::processCombo(std::shared_ptr<Combo> combo) {
  combos.insert(combo);
  locked = true;
  bool isSkillCombo = false;
  for (auto block: combo->blocks) {
    isSkillCombo = block->fallingFromClearing;
    if (isSkillCombo) {
      break;
    }
  }
  int32_t comboSkillChainLevel = 1;
  if (isSkillCombo) {
    skillChainLevel++;
    comboSkillChainLevel = skillChainLevel;
    panelListener.onEvent(playerId, PanelEvent(PanelEventType::SKILL_COMBO));
    score += (1000 * skillChainLevel * skillChainLevel);
  } else {
    if (clearings.empty()) {
      skillChainLevel = 1;
    }
  }
  score += combo->size() > 3 ? combo->size() * combo->size() * 100 : combo->size() * 100;
  combo->skillChainLevel = comboSkillChainLevel;
  for (auto block: combo->blocks) {
    block->blink();
  }
  panelListener.onCombo(combo.get());
  if ((combo->size() >= 4) || (combo->skillChainLevel > 1)) {
    if (combo->size() >= 4) {
      bonusFreezingTime = static_cast<int32_t>(((combo->size() / 2) * FuriousBlocksCoreDefaults::CORE_FREQUENCY));
    }
    if (combo->skillChainLevel > 1) {
      if (combo->skillChainLevel == 2) {
        bonusFreezingTime = static_cast<int32_t>((5 * FuriousBlocksCoreDefaults::CORE_FREQUENCY));
      } else {
        bonusFreezingTime += (combo->skillChainLevel / 2) + FuriousBlocksCoreDefaults::CORE_FREQUENCY;
      }
    }
    freeze(bonusFreezingTime);
  }

  // Create a new clearing
  auto clearing = std::make_shared<Clearing>();

  for (int32_t y = 1; y < Panel::Y; y++) {
    for (int32_t x = 0; x < Panel::X; x++) {
      auto& current = blocks[x][y];
      if (current == nullptr || current->state != BlockState::BLINKING || current->stateTick != FuriousBlocksCoreDefaults::BLOCK_BLINKINGTIME) {
        continue;
      }
      if (y + 1 < Panel::Y) {
        auto& aboveBlock = blocks[x][y + 1];
        auto garbage = getGarbageByBlock(aboveBlock);
        if (aboveBlock && garbage) {
          garbage->blink(combo);
          clearing->addBlockBar(garbage);
        }
      }
      if (y - 1 > 0) {
        auto& belowBlock = blocks[x][y - 1];
        auto garbage = getGarbageByBlock(belowBlock);
        if (belowBlock && garbage) {
          garbage->blink(combo);
          clearing->addBlockBar(garbage);
        }
      }
      if (x + 1 < Panel::X) {
        auto& rightBlock = blocks[x + 1][y];
        auto garbage = getGarbageByBlock(rightBlock);
        if (rightBlock && garbage) {
          garbage->blink(combo);
          clearing->addBlockBar(garbage);
        }
      }
      if (x - 1 > 0) {
        auto& leftBlock = blocks[x - 1][y];
        auto garbage = getGarbageByBlock(leftBlock);
        if (leftBlock && garbage) {
          garbage->blink(combo);
          clearing->addBlockBar(garbage);
        }
      }
    }
  }

  if (!clearing->isEmpty()) {
    clearings.insert(clearing);
  }
}

Garbage* Panel::newGarbage(int32_t width, int32_t height, int32_t owner, bool skill) {
  return new Garbage(*this, width, height, owner, skill);
}

void Panel::submitMove(std::unique_ptr<Move>&& move) {
  this->move = std::move(move);
}
