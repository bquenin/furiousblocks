#include "Panel.h"

using namespace std;

Panel::Panel(int seed, int playerId, BlockType ***initialBlockTypes)
:scrollingEnabled(true), lastIndex(-1), random(nullptr), localTick(0), playerId(0), cursor(new Point()), state(PanelState::IDLE), stateTick(0), levelScrollingSpeed(0), scrollingSpeed(0), scrollingDelta(0), freezingTime(0), bonusFreezingTime(0), skillChainLevel(1), move(nullptr), locked(false), lifting(false), gracing(false), gameOver(false), wallOffset(0), score(0), panelListener(nullptr) {
  Panel(seed, playerId, initialBlockTypes, nullptr);
}

Panel::Panel(int seed, int playerId, BlockType ***initialBlockTypes, PanelListener *panelListener)
:scrollingEnabled(true), lastIndex(-1), random(nullptr), localTick(0), playerId(0), cursor(new Point()), state(PanelState::IDLE), stateTick(0), levelScrollingSpeed(0), scrollingSpeed(0), scrollingDelta(0), freezingTime(0), bonusFreezingTime(0), skillChainLevel(1), move(nullptr), locked(false), lifting(false), gracing(false), gameOver(false), wallOffset(0), score(0), panelListener(nullptr) {
  this->playerId = playerId;
  this->panelListener = panelListener;
  random = new SimpleRNG(seed);
  scrollingSpeed = levelScrollingSpeed = Panel::INITIAL_SCROLLING_SPEED;
  cursor->x = (Panel::X / 2) - 1;
  cursor->y = (Panel::Y_DISPLAY / 2) - 1;
  if (initialBlockTypes != nullptr) {
    for (int y = 1; y < FuriousBlocksCoreDefaults::PANEL_HEIGHT; y++) {
      for (int x = 0; x < FuriousBlocksCoreDefaults::PANEL_WIDTH; x++) {
        blocks[x][y] = initialBlockTypes[x][y] == nullptr ? nullptr : newBlock(initialBlockTypes[x][y]);
      }
    }
  }
  for (int x = 0; x < Panel::X; x++) {
    blocks[x][0] = blocks[x][1] == nullptr ? newRandom(nullptr) : newRandom(blocks[x][1].getType());
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
  wallOffset = 0;
  combos.clear();
  garbages->clear();
  clearings->clear();
  garbageStack->clear();
  stateTick = 0;
  state = PanelState::IDLE;
  for (int y = 1; y < Panel::Y; y++) {
    for (int x = 0; x < Panel::X; x++) {
      blocks[x][y] = nullptr;
    }
  }
}

void Panel::setTransposedBlocks(BlockType ***initialBlockTypes) {
  for (int y = 0; y < initialBlockTypes[0]->length; y++) {
    for (int x = 0; x < initialBlockTypes->length; x++) {
      blocks[y][x] = initialBlockTypes[x][y] == nullptr ? nullptr : newBlock(initialBlockTypes[x][y]);
    }
  }
  for (int x = 0; x < Panel::X; x++) {
    blocks[x][0] = blocks[x][1] == nullptr ? newRandom(nullptr) : newRandom(blocks[x][1].getType());
  }
}

Block *Panel::newRandom(BlockType excludedType) {
  return newRandom(excludedType, 0, 0);
}

Block *Panel::newRandom(BlockType excludedType, int poppingIndex, int skillChainLevel) {
  int randomIndex = random->nextInt() % Panel::numberOfRegularBlocks;
  int index = randomIndex == lastIndex ? (randomIndex + 1) % Panel::numberOfRegularBlocks : randomIndex;
  if (values()[index] == excludedType) {
    index = (index + 1) % Panel::numberOfRegularBlocks;
  }
  return newBlock(values()[lastIndex = index], poppingIndex, skillChainLevel);
}

Block *Panel::newBlock(BlockType blockType) {
  return newBlock(blockType, 0, 0);
}

Block *Panel::newBlock(BlockType blockType, int index, int skillChainLevel) {
  return new Block(random->nextInt(), blockType, index, skillChainLevel);
}

PanelSituation *Panel::onTick(long tick) {
  if (stateTick > 0) {
    stateTick--;
  }
  if (stateTick == 0) {
    switch (state) {
      case PanelState::QUAKING:
        state = PanelState::IDLE;
        break;
      case PanelState::GAMEOVER_PHASE1:
        state = PanelState::GAMEOVER_PHASE2;
        stateTick = FuriousBlocksCoreDefaults::PANEL_QUAKINGTIME - 1;
        break;
      case PanelState::GAMEOVER_PHASE2:
        state = PanelState::GAMEOVER_PHASE3;
        stateTick = TODO
        CastExpression;
        break;
      case PanelState::GAMEOVER_PHASE3:
        break;
      default:
        break;
    }
  }
  switch (state) {
    case PanelState::QUAKING:
    case PanelState::IDLE:
      processMove();
      mechanics(tick);
      Combo *currentCombo = detectCombo();
      if (currentCombo->size() > 0) {
        processCombo(currentCombo);
      }
      scrolling(tick);
      dropGarbages();
      break;
    case PanelState::GAMEOVER_PHASE1:
      if ((stateTick % 4) == 0) {
        for (int i = 0; i < Panel::X; i++) {
          if (blocks[i][Panel::Y_DISPLAY] == nullptr) {
            continue;
          }
          for (int j = Panel::Y_DISPLAY; j > 0; j--) {
            Block *current = blocks[i][j];
            if (!Block->isComputable(current)) {
              continue;
            }
            current->explode(-1);
            break;
          }
        }
      }
      break;
    case PanelState::GAMEOVER_PHASE2:
      break;
    case PanelState::GAMEOVER_PHASE3:
      if ((stateTick % 2) == 0) {
        if (wallOffset != Panel::Y_DISPLAY) {
          wallOffset++;
        }
      }
      break;
    default:
  }
  return getSituation();
}

void Panel::processMove() {
  if (move == nullptr) {
    return;
  }
  int type = move->getType();
  switch (type) {
    case MoveType->BLOCK_SWITCH:
      Block *src = blocks[cursor->x][cursor->y];
      Block *dst = blocks[cursor->x + 1][cursor->y];
      Block *aboveSrc = blocks[cursor->x][cursor->y + 1];
      Block *aboveDst = blocks[cursor->x + 1][cursor->y + 1];
      if ((src == nullptr) && (dst == nullptr)) {
        break;
      }
      if (src != nullptr) {
        if (!Block->isComputable(src)) {
          break;
        }
      }
      if (dst != nullptr) {
        if (!Block->isComputable(dst)) {
          break;
        }
      }
      if ((dst == nullptr) && (aboveDst != nullptr)) {
        if ((aboveDst->getState() == BlockState::SWITCHING_BACK) || (aboveDst->getState() == BlockState::SWITCHING_FORTH)) {
          break;
        }
      }
      if ((src == nullptr) && (aboveSrc != nullptr)) {
        if ((aboveSrc->getState() == BlockState::SWITCHING_BACK) || (aboveSrc->getState() == BlockState::SWITCHING_FORTH)) {
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
        panelListener->onEvent(playerId, new PanelEvent(PanelEventType::CURSOR_SWAP));
      }
      break;
    case MoveType->CURSOR_DOWN:
      if (cursor->y != 1) {
        cursor->y--;
        if (panelListener != nullptr) {
          panelListener->onEvent(playerId, new PanelEvent(PanelEventType::CURSOR_MOVE));
        }
      }
      break;
    case MoveType->CURSOR_LEFT:
      if (cursor->x != 0) {
        cursor->x--;
        if (panelListener != nullptr) {
          panelListener->onEvent(playerId, new PanelEvent(PanelEventType::CURSOR_MOVE));
        }
      }
      break;
    case MoveType->CURSOR_RIGHT:
      if (cursor->x != (Panel::X - 2)) {
        cursor->x++;
        if (panelListener != nullptr) {
          panelListener->onEvent(playerId, new PanelEvent(PanelEventType::CURSOR_MOVE));
        }
      }
      break;
    case MoveType->CURSOR_UP:
      if (cursor->y != (gracing ? Panel::Y_DISPLAY : Panel::Y_DISPLAY - 1)) {
        cursor->y++;
        if (panelListener != nullptr) {
          panelListener->onEvent(playerId, new PanelEvent(PanelEventType::CURSOR_MOVE));
        }
      }
      break;
    case MoveType->LIFT:
      freeze(0);
      if (!lifting && !locked) {
        lifting = true;
        skillChainLevel = 1;
      }
      break;
  }
  move = nullptr;
}

void Panel::dropGarbages() {
  for (auto *&garbage: new LinkedList<Garbage *>(garbageStack)) {
    int y = (Panel::Y_DISPLAY + garbage->height) - 1;
    for (int h = 0, j = y; h < garbage->height; h++, j--) {
      for (int i = 0, w = 0; w < garbage->width; i++, w++) {
        if (blocks[i][j] != nullptr) {
          return;
        }
      }
    }
    garbageStack->remove(garbage);
    int xPos = garbage->width < Panel::X ? random->nextInt() % (Panel::X - garbage->width) : 0;
    garbage->inject(xPos, y);
  }
}

void Panel::scrolling(long tick) {
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
  scrollingSpeed = lifting ? 1 : scrollingEnabled ? levelScrollingSpeed : Integer->MAX_VALUE;
  bool newLine = false;
  if (tick % scrollingSpeed == 0) {
    scrollingDelta++;
    if (scrollingDelta >= FuriousBlocksCoreDefaults::BLOCK_LOGICALHEIGHT) {
      newLine = true;
    }
    scrollingDelta %= FuriousBlocksCoreDefaults::BLOCK_LOGICALHEIGHT;
  }
  if (newLine) {
    newLine();
    gracePeriod();
    if (cursor->y != (gracing ? Panel::Y_DISPLAY : Panel::Y_DISPLAY - 1)) {
      cursor->y++;
    }
  }
}

void Panel::gracePeriod() {
  bool topLineEmpty = true;
  for (auto **&block: blocks) {
    if (block[Panel::Y_DISPLAY] != nullptr) {
      topLineEmpty = false;
      break;
    }
  }
  if (!topLineEmpty) {
    if (gracing) {
      garbageStack->clear();
      gameOver = true;
      state = PanelState::GAMEOVER_PHASE1;
      stateTick = FuriousBlocksCoreDefaults::PANEL_QUAKINGTIME - 1;
    } else {
      lifting = false;
      gracing = true;
      freeze(TODO
      CastExpression);
    }
    return;
  }
  gracing = false;
}

void Panel::freeze(int freezingTime) {
  this->freezingTime = freezingTime;
}

void Panel::newLine() {
  if (lifting) {
    freeze(TODO
    CastExpression);
    scrollingDelta = 0;
  }
  lifting = false;
  for (int y = Panel::Y - 1; y > 0; y--) {
    for (int x = 0; x < Panel::X; x++) {
      blocks[x][y] = blocks[x][y - 1];
    }
  }
  for (int x = 0; x < Panel::X; x++) {
    blocks[x][0] = blocks[x][1] == nullptr ? newRandom(nullptr) : newRandom(blocks[x][1].getType());
  }
}

void Panel::stackGarbage(Garbage *garbage) {
  if (garbage->isSkill()) {
    for (ListIterator<Garbage *> *iterator = garbageStack->listIterator(garbageStack->size()); iterator->hasPrevious();) {
      Garbage *stackedGarbage = iterator->previous();
      if (stackedGarbage->isSkill() && stackedGarbage->height == garbage->height - 1 && stackedGarbage->getOwner() == garbage->getOwner()) {
        iterator->set(garbage);
        return;
      }
    }
  }
  garbageStack->add(garbage);
}

void Panel::quake() {
  state = PanelState::QUAKING;
  stateTick = FuriousBlocksCoreDefaults::PANEL_QUAKINGTIME - 1;
}

void Panel::mechanics(long tick) {
  locked = false;
  int revealingTime = FuriousBlocksCoreDefaults::BLOCK_REVEALINGTIMEBASE;
  for (int y = 1; y < Panel::Y; y++) {
    for (int x = 0; x < Panel::X; x++) {
      Block *current = blocks[x][y];
      if (current == nullptr) {
        continue;
      }
      if (current->hasJustLand()) {
        current->setJustLand();
        current->setFallingFromClearing(false);
      }
      PanelEvent *event = current->update();
      if (event != nullptr) {
        event->data1 = current->getPoppingSkillChainLevel();
        event->data2 = current->getPoppingIndex();
        event->data3 = tick;
        if (panelListener != nullptr) {
          panelListener->onEvent(playerId, event);
        }
      }
      BlockType type = current->getType();
      BlockState state = current->getState();
      switch (state) {
        case BlockState::DONE_SWITCHING_FORTH:
          blocks[x][y] = blocks[x + 1][y];
          blocks[x + 1][y] = current;
          blocks[x][y].idle();
          blocks[x + 1][y].idle();
          if (blocks[x][y].getType() == BlockType::INVISIBLE) {
            blocks[x][y].delete();
          }
          if (blocks[x + 1][y].getType() == BlockType::INVISIBLE) {
            blocks[x + 1][y].delete();
          }
          break;
        case BlockState::TO_DELETE:
          if (type != BlockType::INVISIBLE) {
            for (int k = y + 1; k < Panel::Y; k++) {
              if (!Block->isComputable(blocks[x][k])) {
                break;
              }
              blocks[x][k].setFallingFromClearing(true);
            }
          }
          blocks[x][y] = nullptr;
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
            case BlockType::GARBAGE:
              Garbage *garbage = getGarbageByBlock(current);
              if (garbage->hasToFall(x, y)) {
                garbage->fall(x, y);
              }
              x += garbage->width - 1;
              break;
          }
          break;
        case BlockState::HOVERING:
          break;
        case BlockState::DONE_AIRBOUNCING:
        case BlockState::DONE_HOVERING:
          if (blocks[x][y - 1] == nullptr) {
            for (int k = y + 1; k < Panel::Y; k++) {
              if (blocks[x][k] == nullptr || !blocks[x][k].getType()->movable || blocks[x][k].getType() == BlockType::GARBAGE || blocks[x][k].getState() != BlockState::IDLE) {
                break;
              }
              blocks[x][k].fall();
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
            case BlockType::GARBAGE:
              Garbage *garbage = getGarbageByBlock(current);
              if (garbage->hasToFall(x, y)) {
                garbage->fall(x, y);
              } else {
                garbage->idle();
                quake();
              }
              x += garbage->width - 1;
              break;
          }
          break;
        case BlockState::DONE_BLINKING:
          switch (type) {
            case BlockType::BLUE:
            case BlockType::GREEN:
            case BlockType::PURPLE:
            case BlockType::RED:
            case BlockType::YELLOW:
              Combo *combo = getComboByBlock(current);
              for (auto *&block: combo->getBlocks()) {
                if (block->getState() == BlockState::EXPLODING) {
                  break;
                }
                block->explode(revealingTime += FuriousBlocksCoreDefaults::BLOCK_REVEALINGTIMEINCREMENT);
              }
              break;
            case BlockType::GARBAGE:
              Clearing *clearing = current->getClearing();
              Garbage *garbage = getGarbageByBlock(current);
              revealingTime = garbage->reveal(x, y, revealingTime, clearing);
              clearing->setRevealingTime(tick + revealingTime);
              clearing->removeBar(garbage);
              x += garbage->width - 1;
              break;
          }
          break;
        case BlockState::DONE_EXPLODING:
          switch (type) {
            case BlockType::BLUE:
            case BlockType::GREEN:
            case BlockType::PURPLE:
            case BlockType::RED:
            case BlockType::YELLOW:
              Combo *combo = getComboByBlock(current);
              bool doneExploding = true;
              for (auto *&block: combo->getBlocks()) {
                if (block->getState() != BlockState::DONE_EXPLODING) {
                  doneExploding = false;
                  break;
                }
              }
              if (doneExploding) {
                combos->remove(combo);
                for (auto *&block: combo->getBlocks()) {
                  block->delete();
                }
                combo->getBlocks().clear();
              }
              break;
            case BlockType::GARBAGE:
          }
          break;
        case BlockState::DONE_REVEALING:
          Clearing *clearing = current->getClearing();
          if (clearing->isDoneRevealing(tick)) {
            clearing->onDoneRevealing();
            clearings->remove(clearing);
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
          break;
        default:
      }
    }
  }
}

Combo *Panel::getComboByBlock(Block *block) {
  for (auto *&combo: combos) {
    if (combo->contains(block)) {
      return combo;
    }
  }
  return nullptr;
}

Garbage *Panel::getGarbageByBlock(Block *block) {
  for (auto *&garbage: garbages) {
    if (garbage->contains(block)) {
      return garbage;
    }
  }
  return nullptr;
}

Combo *Panel::detectCombo() {
  Combo *currentCombo = new Combo(playerId);
  bool *comboMask[Panel::X][Panel::Y];
  for (int y = 1; y < Panel::Y; y++) {
    for (int x = 0; x < Panel::X; x++) {
      Block *current = blocks[x][y];
      if (current == nullptr || current->getState() != BlockState::IDLE || !current->getType()->movable || !current->getType()->combinable) {
        continue;
      }
      int xIdem = 1;
      for (int right = x + 1; right < Panel::X; right++) {
        Block *rightBlock = blocks[right][y];
        if (rightBlock == nullptr || rightBlock->getState() != BlockState::IDLE || rightBlock->getType() != current->getType()) {
          break;
        }
        xIdem++;
      }
      int yIdem = 1;
      for (int above = y + 1; above < Panel::Y; above++) {
        Block *aboveBlock = blocks[x][above];
        if (aboveBlock == nullptr || aboveBlock->getState() != BlockState::IDLE || aboveBlock->getType() != current->getType()) {
          break;
        }
        yIdem++;
      }
      if (xIdem >= 3) {
        for (int k = x; k < (x + xIdem); k++) {
          comboMask[k][y] = true;
        }
      }
      if (yIdem >= 3) {
        for (int k = y; k < (y + yIdem); k++) {
          comboMask[x][k] = true;
        }
      }
    }
  }
  int poppingIndex = 0;
  for (int y = Panel::Y - 1; y > 0; y--) {
    for (int x = 0; x < Panel::X; x++) {
      if (!comboMask[x][y]) {
        continue;
      }
      currentCombo->addBlock(blocks[x][y]);
      blocks[x][y].setCombo();
      blocks[x][y].setPoppingIndex(poppingIndex++);
    }
  }
  return currentCombo;
}

void Panel::processCombo(Combo *combo) {
  combos->add(combo);
  locked = true;
  bool isSkillCombo = false;
  for (auto *&block: combo->getBlocks()) {
    isSkillCombo = block->isFallingFromClearing();
    if (isSkillCombo) {
      break;
    }
  }
  int comboSkillChainLevel = 1;
  if (isSkillCombo) {
    skillChainLevel++;
    comboSkillChainLevel = skillChainLevel;
    if (panelListener != nullptr) {
      panelListener->onEvent(playerId, new PanelEvent(PanelEventType::SKILL_COMBO));
    }
    score += (1000 * skillChainLevel) + (combo->size() * 100);
  } else {
    if (clearings->isEmpty()) {
      skillChainLevel = 1;
    }
    score += combo->size() * 100;
  }
  for (auto *&block: combo->getBlocks()) {
    block->setPoppingSkillChainLevel(skillChainLevel);
  }
  combo->skillChainLevel = comboSkillChainLevel;
  for (auto *&block: combo->getBlocks()) {
    block->blink();
  }
  if (panelListener != nullptr) {
    panelListener->onCombo(combo);
  }
  if ((combo->size() >= 4) || (combo->getSkillChainLevel() > 1)) {
    if (combo->size() >= 4) {
      bonusFreezingTime = TODO
      CastExpression;
    }
    if (combo->getSkillChainLevel() > 1) {
      if (combo->getSkillChainLevel() == 2) {
        bonusFreezingTime = TODO
        CastExpression;
      } else {
        bonusFreezingTime += (combo->getSkillChainLevel() / 2) + FuriousBlocksCoreDefaults::CORE_FREQUENCY;
      }
    }
    freeze(bonusFreezingTime);
  }
  int poppingIndex = combo->size();
  Clearing *clearing = new Clearing();
  for (int y = 1; y < Panel::Y; y++) {
    for (int x = 0; x < Panel::X; x++) {
      Block *current = blocks[x][y];
      if (current == nullptr || current->getState() != BlockState::BLINKING || current->getStateTick() != FuriousBlocksCoreDefaults::BLOCK_BLINKINGTIME) {
        continue;
      }
      if (y + 1 < Panel::Y) {
        Block *aboveBlock = blocks[x][y + 1];
        Garbage *garbage = getGarbageByBlock(aboveBlock);
        if (aboveBlock != nullptr && garbage != nullptr) {
          poppingIndex = garbage->blink(poppingIndex, combo);
          clearing->addBlockBar(garbage);
        }
      }
      if (y - 1 > 0) {
        Block *belowBlock = blocks[x][y - 1];
        Garbage *garbage = getGarbageByBlock(belowBlock);
        if (belowBlock != nullptr && garbage != nullptr) {
          poppingIndex = garbage->blink(poppingIndex, combo);
          clearing->addBlockBar(garbage);
        }
      }
      if (x + 1 < Panel::X) {
        Block *rightBlock = blocks[x + 1][y];
        Garbage *garbage = getGarbageByBlock(rightBlock);
        if (rightBlock != nullptr && garbage != nullptr) {
          poppingIndex = garbage->blink(poppingIndex, combo);
          clearing->addBlockBar(garbage);
        }
      }
      if (x - 1 > 0) {
        Block *leftBlock = blocks[x - 1][y];
        Garbage *garbage = getGarbageByBlock(leftBlock);
        if (leftBlock != nullptr && garbage != nullptr) {
          poppingIndex = garbage->blink(poppingIndex, combo);
          clearing->addBlockBar(garbage);
        }
      }
    }
  }
  if (!clearing->isEmpty()) {
    clearings->add(clearing);
  }
}

PanelSituation *Panel::getSituation() {
  BlockSituation *blockSituations[Panel::X][Panel::Y_DISPLAY + 1];
  for (int y = 0; y < (Panel::Y_DISPLAY + 1); y++) {
    for (int x = 0; x < Panel::X; x++) {
      blockSituations[x][y] = blocks[x][y] == nullptr ? nullptr : blocks[x][y].getSituation();
    }
  }
  list<ComboSituation *> *comboSituations = new ArrayList<ComboSituation *>();
  for (auto *&combo: combos) {
    comboSituations->add(combo->getSituation());
  }
  list<GarbageSituation *> *garbageSituations = new ArrayList<GarbageSituation *>();
  for (auto *&garbage: garbages) {
    garbageSituations->add(garbage->getSituation());
  }
  list<GarbageSituation *> *garbageStackSituation = new ArrayList<GarbageSituation *>();
  for (auto *&garbage: garbageStack) {
    garbageStackSituation->add(garbage->getSituation());
  }
  return new PanelSituation(blockSituations, locked, comboSituations, new Point(cursor), scrollingDelta, state, stateTick, garbageSituations, garbageStackSituation, skillChainLevel, freezingTime, gameOver, wallOffset, gracing, score, !clearings->isEmpty());
}

Garbage *Panel::newGarbage(int width, int height, int owner, bool skill) {
  return new Garbage(width, height, owner, skill);
}

long Panel::getLocalTick() {
  return localTick;
}

void Panel::setLocalTick(long localTick) {
  this->localTick = localTick;
}

bool Panel::isGameOver() {
  return gameOver;
}

void Panel::submitMove(Move *move) {
  this->move = new Move(move);
}

int Panel::hashCode() {
  if (blocks == nullptr) {
    return 0;
  }
  int hash = 1;
  for (int x = 0; x < Panel::X; x++) {
    for (int y = 0; y < Panel::Y; y++) {
      hash = 31 * hash + (blocks[x][y] == nullptr ? 0 : blocks[x][y].getId());
    }
  }
  return hash;
}

bool Panel::equals(Object *obj) {
  if (this == obj) {
    return true;
  }
  if (obj == nullptr) {
    return false;
  }
  if (getClass() != obj->getClass()) {
    return false;
  }
  Panel *other = TODO
  CastExpression;
  return blocks->hashCode() == other->hashCode();
}

BlockBar::BlockBar(Panel *__parent, int width, int height, int owner)
:__parent(__parent), id(0), width(0), height(0), owner(0), barBlocks(new HashSet<Block *>()) {
  this->id = random->nextInt();
  this->width = width;
  this->height = height >= Panel::Y - Panel::Y_DISPLAY ? Panel::Y - Panel::Y_DISPLAY : height;
  this->owner = owner;
}

bool BlockBar::contains(Block *block) {
  return barBlocks->contains(block);
}

bool BlockBar::hasToFall(int xOrigin, int yOrigin) {
  for (int x = xOrigin; x < xOrigin + width && x < Panel::X; x++) {
    if (blocks[x][yOrigin - 1] != nullptr) {
      return false;
    }
  }
  return true;
}

void BlockBar::fall(int xOrigin, int yOrigin) {
  for (int y = yOrigin; y < yOrigin + height && y < Panel::Y; y++) {
    for (int x = xOrigin; x < xOrigin + width && x < Panel::X; x++) {
      blocks[x][y - 1] = blocks[x][y];
      blocks[x][y] = nullptr;
    }
  }
}

void BlockBar::idle() {
  for (auto *&block: barBlocks) {
    block->idle();
  }
}

int BlockBar::blink(int poppingIndex) {
  if (barBlocks->iterator().next().getState() == BlockState::BLINKING) {
    return poppingIndex;
  }
  int index = poppingIndex;
  for (auto *&block: barBlocks) {
    block->blink();
    block->setPoppingIndex(index++);
    block->setPoppingSkillChainLevel(skillChainLevel);
  }
  return index;
}

bool BlockBar::isRevealing() {
  for (auto *&block: barBlocks) {
    if (block->getState() == BlockState::REVEALING) {
      return true;
    }
  }
  return false;
}

int BlockBar::hashCode() {
  return id;
}

bool BlockBar::equals(Object *obj) {
  if (this == obj) {
    return true;
  }
  if (obj == nullptr) {
    return false;
  }
  if (getClass() != obj->getClass()) {
    return false;
  }
  BlockBar * other = TODO
  CastExpression;
  if (id != other->id) {
    return false;
  }
  return true;
}

Garbage::Garbage(Panel *__parent, int width, int height, int owner, bool skill)
:__parent(__parent), skill(false), triggeringCombo(nullptr) {
  this->skill = skill;
}

bool Garbage::isSkill() {
  return skill;
}

int Garbage::getOwner() {
  return owner;
}

void Garbage::inject(int x, int y) {
  for (int j = y, h = 0; h < height; j--, h++) {
    for (int i = x, w = 0; w < width; i++, w++) {
      if (blocks[i][j] == nullptr) {
        blocks[i][j] = newBlock(BlockType::GARBAGE);
      } else {
        blocks[i][j] = newBlock(BlockType::GARBAGE, blocks[i][j].getPoppingIndex(), blocks[i][j].getPoppingSkillChainLevel());
      }
      blocks[i][j].setGarbageOwner(owner);
      barBlocks->add(blocks[i][j]);
    }
  }
  garbages->add(this);
  switch (height) {
    case 1:
      for (int w = 1; w < (width - 1); w++) {
        blocks[x + w][y].setGarbageBlockType(GarbageBlockType->UPDOWN);
      }
      blocks[x][y].setGarbageBlockType(GarbageBlockType->UPLEFTDOWN);
      blocks[(x + width) - 1][y].setGarbageBlockType(GarbageBlockType->UPRIGHTDOWN);
      break;
    default:
      for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
          blocks[x + w][y - h].setGarbageBlockType(GarbageBlockType->PLAIN);
        }
      }
      blocks[x][y].setGarbageBlockType(GarbageBlockType->UPLEFT);
      blocks[x][y - (height - 1)].setGarbageBlockType(GarbageBlockType->DOWNLEFT);
      blocks[(x + width) - 1][y].setGarbageBlockType(GarbageBlockType->UPRIGHT);
      blocks[(x + width) - 1][y - (height - 1)].setGarbageBlockType(GarbageBlockType->DOWNRIGHT);
      if (width > 2) {
        for (int w = 1; w < (width - 1); w++) {
          blocks[x + w][y].setGarbageBlockType(GarbageBlockType->UP);
          blocks[x + w][y - (height - 1)].setGarbageBlockType(GarbageBlockType->DOWN);
        }
      }
      if (height > 2) {
        for (int h = 1; h < (height - 1); h++) {
          blocks[x][y - h].setGarbageBlockType(GarbageBlockType->LEFT);
          blocks[(x + width) - 1][y - h].setGarbageBlockType(GarbageBlockType->RIGHT);
        }
      }
      break;
  }
}

int Garbage::blink(int poppingIndex, Combo *combo) {
  triggeringCombo = combo;
  return TODO
  SuperMethodInvocation;
}

int Garbage::reveal(int xOrigin, int yOrigin, int revealingTime, Clearing *parentClearing) {
  if (isRevealing()) {
    return revealingTime;
  }
  garbages->remove(this);
  int revealingTimeIncrement = revealingTime;
  if (triggeringCombo != nullptr) {
    for (auto *&block: triggeringCombo->getBlocks()) {
      if (block->getState() == BlockState::EXPLODING) {
        break;
      }
      block->explode(revealingTimeIncrement += FuriousBlocksCoreDefaults::BLOCK_REVEALINGTIMEINCREMENT);
    }
  }
  BlockLine *subLine = new BlockLine(width, owner);
  subLine->inject(xOrigin, yOrigin);
  parentClearing->addBlockBar(subLine);
  revealingTimeIncrement = subLine->reveal(xOrigin, yOrigin, revealingTimeIncrement);
  if (height > 1) {
    Garbage *subGarbage = newGarbage(width, height - 1, owner, skill);
    subGarbage->inject(xOrigin, yOrigin + height - 1);
    parentClearing->addBlockBar(subGarbage);
    for (int y = yOrigin + 1; y < yOrigin + height && y < Panel::Y; y++) {
      for (int x = xOrigin; x < xOrigin + width && x < Panel::X; x++) {
        if (y <= Panel::Y_DISPLAY) {
          blocks[x][y].reveal(revealingTimeIncrement += FuriousBlocksCoreDefaults::BLOCK_REVEALINGTIMEINCREMENT);
        } else {
          blocks[x][y].reveal(-1);
        }
      }
    }
  }
  return revealingTimeIncrement;
}

void Garbage::onDoneRevealing() {
  for (auto *&block: barBlocks) {
    block->idle();
  }
}

GarbageSituation *Garbage::getSituation() {
  list<Integer *> *blockIds = new ArrayList < Integer * > ();
  for (auto *&barBlock: barBlocks) {
    blockIds->add(barBlock->getId());
  }
  return new GarbageSituation(width, height, owner, blockIds);
}

BlockLine::BlockLine(Panel *__parent, int width, int owner)
:__parent(__parent) {
}

void BlockLine::inject(int x, int y) {
  for (int j = y, h = 0; h < height; j--, h++) {
    for (int i = x, w = 0; w < width; i++, w++) {
      if (blocks[i][j] == nullptr) {
        blocks[i][j] = newRandom(nullptr);
      } else {
        blocks[i][j] = newRandom(nullptr, blocks[i][j].getPoppingIndex(), blocks[i][j].getPoppingSkillChainLevel());
      }
      blocks[i][j].setGarbageOwner(owner);
      barBlocks->add(blocks[i][j]);
    }
  }
}

void BlockLine::onDoneRevealing() {
  for (auto *&block: barBlocks) {
    block->airBounce();
    block->setFallingFromClearing(true);
  }
}

int BlockLine::reveal(int xOrigin, int yOrigin, int revealingTime) {
  if (isRevealing()) {
    return revealingTime;
  }
  int revealingTimeIncrement = revealingTime;
  for (int y = yOrigin; y < yOrigin + height && y < Panel::Y; y++) {
    for (int x = xOrigin; x < xOrigin + width && x < Panel::X; x++) {
      if (y <= Panel::Y_DISPLAY) {
        blocks[x][y].reveal(revealingTimeIncrement += FuriousBlocksCoreDefaults::BLOCK_REVEALINGTIMEINCREMENT);
      } else {
        blocks[x][y].reveal(-1);
      }
    }
  }
  return revealingTimeIncrement;
}

void Clearing::addBlockBar(BlockBar *bar) {
  for (auto *&block: bar->barBlocks) {
    block->setClearing(this);
  }
  bars->add(bar);
}

bool Clearing::isDoneRevealing(long tick) {
  return tick == revealingTime;
}

void Clearing::onDoneRevealing() {
  for (auto *&bar: bars) {
    bar->onDoneRevealing();
  }
}

bool Clearing::contains(Block *block) {
  for (auto *&bar: bars) {
    if (bar->contains(block)) {
      return true;
    }
  }
  return false;
}

bool Clearing::isEmpty() {
  return bars->isEmpty();
}

void Clearing::removeBar(BlockBar *bar) {
  for (auto *&block: bar->barBlocks) {
    block->setClearing(nullptr);
  }
  bars->remove(bar);
}

void Clearing::setRevealingTime(long revealingTime) {
  this->revealingTime = revealingTime;
}

