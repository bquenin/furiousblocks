#include <cstdint>
#include <iostream>
#include <cassert>
#include "Panel.h"
#include "GarbageBlockType.h"

Panel::Panel(int32_t seed, int32_t playerId, std::array<std::array<BlockType, FuriousBlocksCoreDefaults::PANEL_HEIGHT>, FuriousBlocksCoreDefaults::PANEL_WIDTH> initialBlockTypes, PanelListener &panelListener)
: lastIndex(-1)
, random(SimpleRNG(seed))
, localTick(0)
, playerId(playerId)
, cursor(furiousblocks::Point((Panel::X / 2) - 1, (Panel::Y_DISPLAY / 2)))
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

Panel::~Panel() {
  reset();
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

std::unique_ptr<fb::Block> Panel::newRandom(BlockType excludedType, int32_t poppingIndex, int32_t skillChainLevel) {
  int32_t randomIndex = random.nextInt() % Panel::numberOfRegularBlocks;
  int32_t index = randomIndex == lastIndex ? (randomIndex + 1) % Panel::numberOfRegularBlocks : randomIndex;
  if (index == static_cast<int32_t>(excludedType)) {
    index = (index + 1) % Panel::numberOfRegularBlocks;
  }
  return newBlock(static_cast<BlockType>(lastIndex = index), poppingIndex, skillChainLevel);
}

std::unique_ptr<fb::Block> Panel::newBlock(BlockType blockType, int32_t index, int32_t skillChainLevel) {
  return std::unique_ptr<fb::Block>(new fb::Block(random.nextInt(), blockType, index, skillChainLevel));
}

void Panel::onTick(int64_t tick) {
  processMove();
  mechanics(tick);
  std::shared_ptr<Combo> currentCombo(detectCombo());
  if (currentCombo->size() > 0) {
    processCombo(currentCombo);
  } else {
    currentCombo.reset();
  }
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
//      std::unique_ptr<fb::Block>& src = blocks[cursor.x][cursor.y];
//      std::unique_ptr<fb::Block>& dst = blocks[cursor.x + 1][cursor.y];
//      std::unique_ptr<fb::Block>& aboveSrc = blocks[cursor.x][cursor.y + 1];
//      std::unique_ptr<fb::Block>& aboveDst = blocks[cursor.x + 1][cursor.y + 1];
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
  std::set<Panel::Garbage*> duplicata(garbageStack);
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

void Panel::stackGarbage(Panel::Garbage* garbage) {
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
      std::unique_ptr<PanelEvent> event = current->update();
      if (event != nullptr) {
        event->data1 = current->poppingSkillChainLevel;
        event->data2 = current->poppingIndex;
        event->data3 = static_cast<int32_t>(tick);
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
              auto clearing = static_cast<Clearing*>(current->clearing);
              auto garbage = getGarbageByBlock(current);
              revealingTime = garbage->reveal(x, y, revealingTime, clearing);
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
          Clearing* clearing = static_cast<Clearing*>(current->clearing);
          if (clearing->isDoneRevealing(tick)) {
            clearing->onDoneRevealing();
            clearings.erase(clearing);
            delete clearing;
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

std::shared_ptr<Panel::Garbage> Panel::getGarbageByBlock(std::shared_ptr<fb::Block> block) {
  for (auto &garbage: garbages) {
    if (garbage->contains(block)) {
      return garbage;
    }
  }
  return nullptr;
}

std::shared_ptr<Combo> Panel::detectCombo() {
  std::shared_ptr<Combo> currentCombo(new Combo(playerId));

  for (int32_t y = 0; y < Panel::Y; y++) {
    for (int32_t x = 0; x < Panel::X; x++) {
      comboMask[x][y] = false;
    }
  }
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
  int32_t poppingIndex = 0;
  for (int32_t y = Panel::Y - 1; y > 0; y--) {
    for (int32_t x = 0; x < Panel::X; x++) {
      if (!comboMask[x][y]) {
        continue;
      }
      if (poppingIndex == 0) {
        currentCombo->x = x;
        currentCombo->y = y;
      }
      currentCombo->addBlock(blocks[x][y]);
      blocks[x][y]->combo = true;
      blocks[x][y]->poppingIndex = poppingIndex++;
    }
  }
  return currentCombo;
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
  for (auto block: combo->blocks) {
    block->poppingSkillChainLevel = skillChainLevel;
  }
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
  int32_t poppingIndex = combo->size();
  Clearing* clearing = new Clearing();
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
          poppingIndex = garbage->blink(poppingIndex, combo);
          clearing->addBlockBar(garbage);
        }
      }
      if (y - 1 > 0) {
        auto& belowBlock = blocks[x][y - 1];
        auto garbage = getGarbageByBlock(belowBlock);
        if (belowBlock && garbage) {
          poppingIndex = garbage->blink(poppingIndex, combo);
          clearing->addBlockBar(garbage);
        }
      }
      if (x + 1 < Panel::X) {
        auto& rightBlock = blocks[x + 1][y];
        auto garbage = getGarbageByBlock(rightBlock);
        if (rightBlock && garbage) {
          poppingIndex = garbage->blink(poppingIndex, combo);
          clearing->addBlockBar(garbage);
        }
      }
      if (x - 1 > 0) {
        auto& leftBlock = blocks[x - 1][y];
        auto garbage = getGarbageByBlock(leftBlock);
        if (leftBlock && garbage) {
          poppingIndex = garbage->blink(poppingIndex, combo);
          clearing->addBlockBar(garbage);
        }
      }
    }
  }
  if (!clearing->isEmpty()) {
    clearings.insert(clearing);
  } else {
    delete clearing;
  }
}

//PanelSituation *Panel::getSituation() {
//  BlockSituation ***blockSituations = new BlockSituation **[FuriousBlocksCoreDefaults::PANEL_WIDTH];
//  for (int x = 0; x < FuriousBlocksCoreDefaults::PANEL_WIDTH; x++) {
//    blockSituations[x] = new BlockSituation *[FuriousBlocksCoreDefaults::PANEL_HEIGHT + 1];
//    for (int y = 0; y < FuriousBlocksCoreDefaults::PANEL_HEIGHT + 1; y++) {
//      blockSituations[x][y] = blocks[x][y] == NULL ? NULL : blocks[x][y]->getSituation();
//    }
//  }
//
//  std::set<ComboSituation *> comboSituations;
//  for (auto combo: combos) {
//    comboSituations.insert(combo->getSituation());
//  }
//  std::set<GarbageSituation *> garbageSituations;
//  for (auto garbage: garbages) {
//    garbageSituations.insert(garbage->getSituation());
//  }
//  std::set<GarbageSituation *> garbageStackSituation;
//  for (auto garbage: garbageStack) {
//    garbageStackSituation.insert(garbage->getSituation());
//  }
//  return new PanelSituation(blockSituations, locked, comboSituations, cursor, scrollingDelta, state, stateTick, garbageSituations, garbageStackSituation, skillChainLevel, freezingTime, gameOver, wallOffset, gracing, score, !clearings.empty());
//}

Panel::Garbage* Panel::newGarbage(int32_t width, int32_t height, int32_t owner, bool skill) {
  return new Panel::Garbage(this, width, height, owner, skill);
}

int64_t Panel::getLocalTick() {
  return localTick;
}

void Panel::setLocalTick(int64_t localTick) {
  this->localTick = localTick;
}

bool Panel::isGameOver() const {
  return gameOver;
}

void Panel::submitMove(std::unique_ptr<Move, MoveDeleter>&& move) {
  this->move = std::move(move);
}

Panel::BlockBar::BlockBar(Panel* __parent, int32_t width, int32_t height, int32_t owner)
: __parent (__parent) {
  this->id = __parent->random.nextInt();
  this->width = width;
  this->height = height >= Panel::Y - Panel::Y_DISPLAY ? Panel::Y - Panel::Y_DISPLAY : height;
  this->owner = owner;
}

bool Panel::BlockBar::contains(std::shared_ptr<fb::Block> block) {
  return barBlocks.find(block) != barBlocks.end();
}

bool Panel::BlockBar::hasToFall(int32_t xOrigin, int32_t yOrigin) {
  for (int32_t x = xOrigin; x < xOrigin + width && x < Panel::X; x++) {
    if (__parent->blocks[x][yOrigin - 1] != nullptr) {
      return false;
    }
  }
  return true;
}

void Panel::BlockBar::fall(int32_t xOrigin, int32_t yOrigin) {
  for (int32_t y = yOrigin; y < yOrigin + height && y < Panel::Y; y++) {
    for (int32_t x = xOrigin; x < xOrigin + width && x < Panel::X; x++) {
      __parent->blocks[x][y - 1] = __parent->blocks[x][y];
      __parent->blocks[x][y] = nullptr;
    }
  }
}

void Panel::BlockBar::idle() {
  for (auto block: barBlocks) {
    block->idle();
  }
}

int32_t Panel::BlockBar::blink(int32_t poppingIndex) {
  auto first = barBlocks.begin();
  if ((*first)->state == BlockState::BLINKING) {
    return poppingIndex;
  }
  //  if (barBlocks->iterator()->next()->state == BlockState::BLINKING) {
  //    return poppingIndex;
  //  }
  int32_t index = poppingIndex;
  for (auto block: barBlocks) {
    block->blink();
    int32_t poppingIndex1 = index++;
    block->poppingIndex = poppingIndex1;
    block->poppingSkillChainLevel = __parent->skillChainLevel;
  }
  return index;
}

bool Panel::BlockBar::isRevealing() {
  for (auto block: barBlocks) {
    if (block->state == BlockState::REVEALING) {
      return true;
    }
  }
  return false;
}

Panel::Garbage::Garbage(Panel* __parent, int32_t width, int32_t height, int32_t owner, bool skill)
: BlockBar(__parent, width, height, owner) {
  this->skill = skill;
}

bool Panel::Garbage::isSkill() {
  return skill;
}

int32_t Panel::Garbage::getOwner() {
  return owner;
}

void Panel::Garbage::inject(int32_t x, int32_t y) {
  for (int32_t j = y, h = 0; h < height; j--, h++) {
    for (int32_t i = x, w = 0; w < width; i++, w++) {
      if (__parent->blocks[i][j] == nullptr) {
        __parent->blocks[i][j] = __parent->newBlock(BlockType::GARBAGE);
      } else {
        __parent->blocks[i][j] = __parent->newBlock(BlockType::GARBAGE, __parent->blocks[i][j]->poppingIndex, __parent->blocks[i][j]->poppingSkillChainLevel);
      }
      __parent->blocks[i][j]->garbageOwner = owner;
      barBlocks.insert(__parent->blocks[i][j]);
    }
  }
  __parent->garbages.insert(std::shared_ptr<Panel::Garbage>(this));
  switch (height) {
    case 1:
      for (int32_t w = 1; w < (width - 1); w++) {
        __parent->blocks[x + w][y]->garbageBlockType = GarbageBlockType::UPDOWN;
      }
      __parent->blocks[x][y]->garbageBlockType = GarbageBlockType::UPLEFTDOWN;
      __parent->blocks[(x + width) - 1][y]->garbageBlockType = GarbageBlockType::UPRIGHTDOWN;
      break;
    default:
      for (int32_t h = 0; h < height; h++) {
        for (int32_t w = 0; w < width; w++) {
          __parent->blocks[x + w][y - h]->garbageBlockType = GarbageBlockType::PLAIN;
        }
      }
      __parent->blocks[x][y]->garbageBlockType = GarbageBlockType::UPLEFT;
      __parent->blocks[x][y - (height - 1)]->garbageBlockType = GarbageBlockType::DOWNLEFT;
      __parent->blocks[(x + width) - 1][y]->garbageBlockType = GarbageBlockType::UPRIGHT;
      __parent->blocks[(x + width) - 1][y - (height - 1)]->garbageBlockType = GarbageBlockType::DOWNRIGHT;
      if (width > 2) {
        for (int32_t w = 1; w < (width - 1); w++) {
          __parent->blocks[x + w][y]->garbageBlockType = GarbageBlockType::UP;
          __parent->blocks[x + w][y - (height - 1)]->garbageBlockType = GarbageBlockType::DOWN;
        }
      }
      if (height > 2) {
        for (int32_t h = 1; h < (height - 1); h++) {
          __parent->blocks[x][y - h]->garbageBlockType = GarbageBlockType::LEFT;
          __parent->blocks[(x + width) - 1][y - h]->garbageBlockType = GarbageBlockType::RIGHT;
        }
      }
      break;
  }
}

int32_t Panel::Garbage::blink(int32_t poppingIndex, std::shared_ptr<Combo> combo) {
  triggeringCombo = combo;
  return BlockBar::blink(poppingIndex);
}

int32_t Panel::Garbage::reveal(int32_t xOrigin, int32_t yOrigin, int32_t revealingTime, Clearing* parentClearing) {
  if (isRevealing()) {
    return revealingTime;
  }

  for (auto garbage = std::next(__parent->garbages.begin()); garbage != __parent->garbages.end(); ++garbage) {
    if (garbage->get() == this) {
      __parent->garbages.erase(garbage);
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
  std::shared_ptr<Panel::BlockLine> subLine(new Panel::BlockLine(__parent, width, owner));
  subLine->inject(xOrigin, yOrigin);
  parentClearing->addBlockBar(subLine);
  revealingTimeIncrement = subLine->reveal(xOrigin, yOrigin, revealingTimeIncrement);
  if (height > 1) {
    std::shared_ptr<Panel::Garbage> subGarbage (__parent->newGarbage(width, height - 1, owner, skill));
    subGarbage->inject(xOrigin, yOrigin + height - 1);
    parentClearing->addBlockBar(subGarbage);
    for (int32_t y = yOrigin + 1; y < yOrigin + height && y < Panel::Y; y++) {
      for (int32_t x = xOrigin; x < xOrigin + width && x < Panel::X; x++) {
        if (y <= Panel::Y_DISPLAY) {
          __parent->blocks[x][y]->reveal(revealingTimeIncrement += FuriousBlocksCoreDefaults::BLOCK_REVEALINGTIMEINCREMENT);
        } else {
          __parent->blocks[x][y]->reveal(-1);
        }
      }
    }
  }
  return revealingTimeIncrement;
}

void Panel::Garbage::onDoneRevealing() {
  for (auto block: barBlocks) {
    block->idle();
  }
}

//GarbageSituation *Panel::Garbage::getSituation() {
//  std::unordered_set<int32_t> blockIds;
//  for (auto barBlock: barBlocks) {
//    blockIds.insert(barBlock->id);
//  }
//  return new GarbageSituation(width, height, owner, blockIds);
//}

Panel::BlockLine::BlockLine(Panel* __parent, int32_t width, int32_t owner)
: BlockBar(__parent, width, 1, owner) {
}

void Panel::BlockLine::inject(int32_t x, int32_t y) {
  for (int32_t j = y, h = 0; h < height; j--, h++) {
    for (int32_t i = x, w = 0; w < width; i++, w++) {
      if (__parent->blocks[i][j] == nullptr) {
        __parent->blocks[i][j] = __parent->newRandom();
      } else {
        __parent->blocks[i][j] = __parent->newRandom(static_cast<BlockType>(-1), __parent->blocks[i][j]->poppingIndex, __parent->blocks[i][j]->poppingSkillChainLevel);
      }
      __parent->blocks[i][j]->garbageOwner = owner;
      barBlocks.insert(__parent->blocks[i][j]);
    }
  }
}

void Panel::BlockLine::onDoneRevealing() {
  for (auto block: barBlocks) {
    block->airBounce();
    block->fallingFromClearing = true;
  }
}

int32_t Panel::BlockLine::reveal(int32_t xOrigin, int32_t yOrigin, int32_t revealingTime) {
  if (isRevealing()) {
    return revealingTime;
  }
  int32_t revealingTimeIncrement = revealingTime;
  for (int32_t y = yOrigin; y < yOrigin + height && y < Panel::Y; y++) {
    for (int32_t x = xOrigin; x < xOrigin + width && x < Panel::X; x++) {
      if (y <= Panel::Y_DISPLAY) {
        __parent->blocks[x][y]->reveal(revealingTimeIncrement += FuriousBlocksCoreDefaults::BLOCK_REVEALINGTIMEINCREMENT);
      } else {
        __parent->blocks[x][y]->reveal(-1);
      }
    }
  }
  return revealingTimeIncrement;
}

void Panel::Clearing::addBlockBar(std::shared_ptr<Panel::BlockBar> bar) {
  for (auto &block: bar->barBlocks) {
    block->clearing = this;
  }
  bars.insert(bar);
}

bool Panel::Clearing::isDoneRevealing(int64_t tick) {
  return tick == revealingTime;
}

void Panel::Clearing::onDoneRevealing() {
  for (auto bar: bars) {
    bar->onDoneRevealing();
  }
}

bool Panel::Clearing::contains(std::shared_ptr<fb::Block> block) {
  for (auto bar: bars) {
    if (bar->contains(block)) {
      return true;
    }
  }
  return false;
}

bool Panel::Clearing::isEmpty() {
  return bars.empty();
}

void Panel::Clearing::removeBar(std::shared_ptr<BlockBar> bar) {
  for (auto block : bar->barBlocks) {
    block->clearing = nullptr;
  }
  bars.erase(bar);
}

void Panel::Clearing::setRevealingTime(int64_t revealingTime) {
  this->revealingTime = revealingTime;
}
