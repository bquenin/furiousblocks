#include <cstdint>
#include "Panel.h"
#include "GarbageBlockType.h"

Panel::Panel(int32_t seed, int32_t playerId, const BlockType initialBlockTypes[FuriousBlocksCoreDefaults::PANEL_WIDTH][FuriousBlocksCoreDefaults::PANEL_HEIGHT], PanelListener *panelListener)
: lastIndex(-1)
, random(new SimpleRNG(seed))
, localTick(0)
, playerId(playerId)
, cursor(new furiousblocks::Point((Panel::X / 2) - 1, (Panel::Y_DISPLAY / 2)))
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
, scrollingEnabled(true) {
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
      if (blocks[x][y] != nullptr) {
        delete blocks[x][y];
      }
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

Block *Panel::newRandom(BlockType excludedType, int32_t poppingIndex, int32_t skillChainLevel) {
  int32_t randomIndex = random->nextInt() % Panel::numberOfRegularBlocks;
  int32_t index = randomIndex == lastIndex ? (randomIndex + 1) % Panel::numberOfRegularBlocks : randomIndex;
  if (index == static_cast<int32_t>(excludedType)) {
    index = (index + 1) % Panel::numberOfRegularBlocks;
  }
  return newBlock(static_cast<BlockType>(lastIndex = index), poppingIndex, skillChainLevel);
}

Block *Panel::newBlock(BlockType blockType, int32_t index, int32_t skillChainLevel) {
  return new Block(random->nextInt(), blockType, index, skillChainLevel);
}

void Panel::onTick(int64_t tick) {
  processMove();
  mechanics(tick);
  Combo *currentCombo = detectCombo();
  if (currentCombo->size() > 0) {
    processCombo(currentCombo);
  } else {
    delete currentCombo;
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
      Block *src = blocks[cursor->x][cursor->y];
      Block *dst = blocks[cursor->x + 1][cursor->y];
      Block *aboveSrc = blocks[cursor->x][cursor->y + 1];
      Block *aboveDst = blocks[cursor->x + 1][cursor->y + 1];
      if ((src == nullptr) && (dst == nullptr)) {
        break;
      }
      if (src != nullptr) {
        if (!Block::isComputable(src)) {
          break;
        }
      }
      if (dst != nullptr) {
        if (!Block::isComputable(dst)) {
          break;
        }
      }
      if ((dst == nullptr) && (aboveDst != nullptr)) {
        if ((aboveDst->state == BlockState::SWITCHING_BACK) || (aboveDst->state == BlockState::SWITCHING_FORTH)) {
          break;
        }
      }
      if ((src == nullptr) && (aboveSrc != nullptr)) {
        if ((aboveSrc->state == BlockState::SWITCHING_BACK) || (aboveSrc->state == BlockState::SWITCHING_FORTH)) {
          break;
        }
      }
      if (src == nullptr) {
        src = blocks[cursor->x][cursor->y] = newBlock(BlockType::INVISIBLE);
      }
      if (dst == nullptr) {
        dst = blocks[cursor->x + 1][cursor->y] = newBlock(BlockType::INVISIBLE);
      }
      src->switchForth();
      dst->switchBack();
      if (panelListener != nullptr) {
        panelListener->onEvent(playerId, PanelEvent(PanelEventType::CURSOR_SWAP));
      }
    }
      break;
    case MoveType::CURSOR_DOWN:
      if (cursor->y != 1) {
        cursor->y--;
        if (panelListener != nullptr) {
          panelListener->onEvent(playerId, PanelEvent(PanelEventType::CURSOR_MOVE));
        }
      }
      break;
    case MoveType::CURSOR_LEFT:
      if (cursor->x != 0) {
        cursor->x--;
        if (panelListener != nullptr) {
          panelListener->onEvent(playerId, PanelEvent(PanelEventType::CURSOR_MOVE));
        }
      }
      break;
    case MoveType::CURSOR_RIGHT:
      if (cursor->x != (Panel::X - 2)) {
        cursor->x++;
        if (panelListener != nullptr) {
          panelListener->onEvent(playerId, PanelEvent(PanelEventType::CURSOR_MOVE));
        }
      }
      break;
    case MoveType::CURSOR_UP:
      if (cursor->y != (gracing ? Panel::Y_DISPLAY : Panel::Y_DISPLAY - 1)) {
        cursor->y++;
        if (panelListener != nullptr) {
          panelListener->onEvent(playerId, PanelEvent(PanelEventType::CURSOR_MOVE));
        }
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
  std::set<Panel::Garbage *> duplicata(garbageStack);
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
    int32_t xPos = garbage->width < Panel::X ? random->nextInt() % (Panel::X - garbage->width) : 0;
    garbage->inject(xPos, y);
  }
}

void Panel::scrolling(int64_t tick) {
  if (((tick % Panel::NEXT_LEVEL) == 0) && (levelScrollingSpeed > 1)) {
    levelScrollingSpeed /= 2;
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
    if (cursor->y != (gracing ? Panel::Y_DISPLAY : Panel::Y_DISPLAY - 1)) {
      cursor->y++;
    }
  }
}

void Panel::gracePeriod() {
  bool topLineEmpty = true;
  for (auto block: blocks) {
    if (block[Panel::Y_DISPLAY] != nullptr) {
      topLineEmpty = false;
      break;
    }
  }
  if (!topLineEmpty) {
    if (gracing) {
      garbageStack.clear();
      gameOver = true;
      panelListener->onGameOver();
    } else {
      lifting = false;
      gracing = true;
      freeze(static_cast<int32_t>((FuriousBlocksCoreDefaults::CORE_FREQUENCY * 2)));
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
    freeze(static_cast<int32_t>(FuriousBlocksCoreDefaults::CORE_FREQUENCY));
    scrollingDelta = 0;
  }
  lifting = false;
  for (int32_t y = Panel::Y - 1; y > 0; y--) {
    for (int32_t x = 0; x < Panel::X; x++) {
      blocks[x][y] = blocks[x][y - 1];
    }
  }
  for (int32_t x = 0; x < Panel::X; x++) {
    blocks[x][0] = blocks[x][1] == nullptr ? newRandom() : newRandom(blocks[x][1]->type);
  }
}

void Panel::stackGarbage(Panel::Garbage *garbage) {
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
      Block *current = blocks[x][y];
      if (current == nullptr) {
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
        if (panelListener != nullptr) {
          panelListener->onEvent(playerId, *event);
        }
      }
      BlockType type = current->type;
      BlockState state = current->state;
      switch (state) {
        case BlockState::DONE_SWITCHING_FORTH:
          blocks[x][y] = blocks[x + 1][y];
          blocks[x + 1][y] = current;
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
              if (!Block::isComputable(blocks[x][k])) {
                break;
              }
              blocks[x][k]->fallingFromClearing = true;
            }
          }
          blocks[x][y] = nullptr;
          delete current;
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
              Panel::Garbage *garbage = getGarbageByBlock(current);
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
            blocks[x][y - 1] = current;
            blocks[x][y] = nullptr;
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
                blocks[x][y - 1] = current;
                blocks[x][y] = nullptr;
              } else {
                current->land();
              }
              break;
            case BlockType::GARBAGE: {
              Panel::Garbage *garbage = getGarbageByBlock(current);
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
              Combo *combo = getComboByBlock(current);
              for (auto block: combo->blocks) {
                if (block->state == BlockState::EXPLODING) {
                  break;
                }
                block->explode(revealingTime += FuriousBlocksCoreDefaults::BLOCK_REVEALINGTIMEINCREMENT);
              }
            }
              break;
            case BlockType::GARBAGE: {
              Clearing *clearing = static_cast<Clearing *>(current->clearing);
              Panel::Garbage *garbage = getGarbageByBlock(current);
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
              Combo *combo = getComboByBlock(current);
              bool doneExploding = true;
              for (auto block: combo->blocks) {
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
                delete combo;
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
          Clearing *clearing = static_cast<Clearing *>(current->clearing);
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

Combo *Panel::getComboByBlock(Block *block) {
  for (auto combo: combos) {
    if (combo->contains(block)) {
      return combo;
    }
  }
  return nullptr;
}

Panel::Garbage *Panel::getGarbageByBlock(Block *block) {
  for (auto garbage: garbages) {
    if (garbage->contains(block)) {
      return garbage;
    }
  }
  return nullptr;
}

Combo *Panel::detectCombo() {
  Combo *currentCombo = new Combo(playerId);

  for (int32_t y = 0; y < Panel::Y; y++) {
    for (int32_t x = 0; x < Panel::X; x++) {
      comboMask[x][y] = false;
    }
  }
  for (int32_t y = 1; y < Panel::Y; y++) {
    for (int32_t x = 0; x < Panel::X; x++) {
      Block *current = blocks[x][y];
      if (current == nullptr || current->state != BlockState::IDLE || !current->movable || !current->combinable) {
        continue;
      }
      int32_t xIdem = 1;
      for (int32_t right = x + 1; right < Panel::X; right++) {
        Block *rightBlock = blocks[right][y];
        if (rightBlock == nullptr || rightBlock->state != BlockState::IDLE || rightBlock->type != current->type) {
          break;
        }
        xIdem++;
      }
      int32_t yIdem = 1;
      for (int32_t above = y + 1; above < Panel::Y; above++) {
        Block *aboveBlock = blocks[x][above];
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

void Panel::processCombo(Combo *combo) {
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
    if (panelListener != nullptr) {
      panelListener->onEvent(playerId, PanelEvent(PanelEventType::SKILL_COMBO));
    }
    score += (1000 * skillChainLevel) + (combo->size() * 100);
  } else {
    if (clearings.empty()) {
      skillChainLevel = 1;
    }
    score += combo->size() * 100;
  }
  for (auto block: combo->blocks) {
    block->poppingSkillChainLevel = skillChainLevel;
  }
  combo->skillChainLevel = comboSkillChainLevel;
  for (auto block: combo->blocks) {
    block->blink();
  }
  if (panelListener != nullptr) {
    panelListener->onCombo(combo);
  }
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
  Clearing *clearing = new Clearing();
  for (int32_t y = 1; y < Panel::Y; y++) {
    for (int32_t x = 0; x < Panel::X; x++) {
      Block *current = blocks[x][y];
      if (current == nullptr || current->state != BlockState::BLINKING || current->stateTick != FuriousBlocksCoreDefaults::BLOCK_BLINKINGTIME) {
        continue;
      }
      if (y + 1 < Panel::Y) {
        Block *aboveBlock = blocks[x][y + 1];
        Panel::Garbage *garbage = getGarbageByBlock(aboveBlock);
        if (aboveBlock != nullptr && garbage != nullptr) {
          poppingIndex = garbage->blink(poppingIndex, combo);
          clearing->addBlockBar(garbage);
        }
      }
      if (y - 1 > 0) {
        Block *belowBlock = blocks[x][y - 1];
        Panel::Garbage *garbage = getGarbageByBlock(belowBlock);
        if (belowBlock != nullptr && garbage != nullptr) {
          poppingIndex = garbage->blink(poppingIndex, combo);
          clearing->addBlockBar(garbage);
        }
      }
      if (x + 1 < Panel::X) {
        Block *rightBlock = blocks[x + 1][y];
        Panel::Garbage *garbage = getGarbageByBlock(rightBlock);
        if (rightBlock != nullptr && garbage != nullptr) {
          poppingIndex = garbage->blink(poppingIndex, combo);
          clearing->addBlockBar(garbage);
        }
      }
      if (x - 1 > 0) {
        Block *leftBlock = blocks[x - 1][y];
        Panel::Garbage *garbage = getGarbageByBlock(leftBlock);
        if (leftBlock != nullptr && garbage != nullptr) {
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

Panel::Garbage *Panel::newGarbage(int32_t width, int32_t height, int32_t owner, bool skill) {
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

Panel::BlockBar::BlockBar(Panel *__parent, int32_t width, int32_t height, int32_t owner)
: __parent (__parent) {
  this->id = __parent->random->nextInt();
  this->width = width;
  this->height = height >= Panel::Y - Panel::Y_DISPLAY ? Panel::Y - Panel::Y_DISPLAY : height;
  this->owner = owner;
}

bool Panel::BlockBar::contains(Block *block) {
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
  std::set<Block *>::const_iterator first = barBlocks.begin();
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

Panel::Garbage::Garbage(Panel *__parent, int32_t width, int32_t height, int32_t owner, bool skill)
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
  __parent->garbages.insert(this);
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

int32_t Panel::Garbage::blink(int32_t poppingIndex, Combo *combo) {
  triggeringCombo = combo;
  return BlockBar::blink(poppingIndex);
}

int32_t Panel::Garbage::reveal(int32_t xOrigin, int32_t yOrigin, int32_t revealingTime, Clearing *parentClearing) {
  if (isRevealing()) {
    return revealingTime;
  }
  __parent->garbages.erase(this);
  int32_t revealingTimeIncrement = revealingTime;
  if (triggeringCombo != nullptr) {
    for (auto block: triggeringCombo->blocks) {
      if (block->state == BlockState::EXPLODING) {
        break;
      }
      block->explode(revealingTimeIncrement += FuriousBlocksCoreDefaults::BLOCK_REVEALINGTIMEINCREMENT);
    }
  }
  Panel::BlockLine *subLine = new Panel::BlockLine(__parent, width, owner);
  subLine->inject(xOrigin, yOrigin);
  parentClearing->addBlockBar(subLine);
  revealingTimeIncrement = subLine->reveal(xOrigin, yOrigin, revealingTimeIncrement);
  if (height > 1) {
    Panel::Garbage *subGarbage = __parent->newGarbage(width, height - 1, owner, skill);
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

Panel::BlockLine::BlockLine(Panel *__parent, int32_t width, int32_t owner)
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

void Panel::Clearing::addBlockBar(Panel::BlockBar *bar) {
  for (auto block: bar->barBlocks) {
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

bool Panel::Clearing::contains(Block *block) {
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

void Panel::Clearing::removeBar(Panel::BlockBar *bar) {
  for (auto block: bar->barBlocks) {
    block->clearing = nullptr;
  }
  bars.erase(bar);
}

void Panel::Clearing::setRevealingTime(int64_t revealingTime) {
  this->revealingTime = revealingTime;
}
