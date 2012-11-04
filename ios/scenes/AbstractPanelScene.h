//
// Created by bquenin on 11/2/12.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __AbstractPanelScene_H_
#define __AbstractPanelScene_H_

#include <iostream>
#include "Animation.h"
#include "Combo.h"
#include "FuriousBlocksCore.h"
#include "NonLoopingAnimation.h"
#include "tweener_group.hpp"
#include "cocos2d.h"

class AbstractPanelScene : public cocos2d::CCLayer {
public:
  static constexpr int32_t
  TILE_SIZE = 48;
  static constexpr int32_t
  xOffset = 17; // 17
  static constexpr int32_t
  yOffset = -38; // 10

  AbstractPanelScene();

  bool init();
  cocos2d::CCSpriteFrame *getBlockFrame(Block *blockSituation, int64_t tick, bool compressed, bool panicking);
  std::string format(char const *fmt, ...);

  // Core
  FuriousBlocksCore *core;
  bool gameRunning;
  int64_t tick;

  // Renderer
  float stateTime;
  cocos2d::CCSprite *grid[FuriousBlocksCoreDefaults::PANEL_WIDTH][FuriousBlocksCoreDefaults::PANEL_HEIGHT + 1];
  std::unordered_map<int32_t, NonLoopingAnimation *> animations;
  claw::tween::tweener_group tweeners;

  // Assets
  cocos2d::CCSpriteBatchNode *batch;

  cocos2d::CCSpriteFrame *BLOCKS_RED_PANIC_01;
  cocos2d::CCSpriteFrame *BLOCKS_BLUE_HOVER_01;
  cocos2d::CCSpriteFrame *BLOCKS_GREEN_COMPRESSED_01;
  cocos2d::CCSpriteFrame *BLOCKS_BLUE_FLASH;
  cocos2d::CCSpriteFrame *GARBAGE_BLINK;
  cocos2d::CCSpriteFrame *BLOCKS_PURPLE_PANIC_01;
  cocos2d::CCSpriteFrame *BLOCKS_RED_LAND_02;
  cocos2d::CCSpriteFrame *BLOCKS_YELLOW_HAPPY;
  cocos2d::CCSpriteFrame *BLOCKS_RED_PANIC_03;
  cocos2d::CCSpriteFrame *BLOCKS_BLUE_HAPPY;
  cocos2d::CCSpriteFrame *BLOCKS_BLUE_PANIC_01;
  cocos2d::CCSpriteFrame *CURSOR_01;
  cocos2d::CCSpriteFrame *GARBAGE_TOP;
  cocos2d::CCSpriteFrame *CURSOR_03;
  cocos2d::CCSpriteFrame *BLOCKS_YELLOW_HOVER_03;
  cocos2d::CCSpriteFrame *BLOCKS_PURPLE_HOVER_01;
  cocos2d::CCSpriteFrame *BLOCKS_YELLOW_HOVER_02;
  cocos2d::CCSpriteFrame *BLOCKS_GREEN_IDLE;
  //  CCSpriteFrame *DRAW;
  cocos2d::CCSpriteFrame *BLOCKS_BLUE_PANIC_02;
  //  CCSpriteFrame *WIN;
  cocos2d::CCSpriteFrame *BLOCKS_GREEN_FLASH;
  cocos2d::CCSpriteFrame *BLOCKS_RED_HOVER_04;
  cocos2d::CCSpriteFrame *BLOCKS_RED_PANIC_04;
  cocos2d::CCSpriteFrame *GARBAGE_RIGHT_BOTTOM;
  cocos2d::CCSpriteFrame *GARBAGE_TOP_RIGHT_BOTTOM;
  cocos2d::CCSpriteFrame *BLOCKS_BLUE_PANIC_04;
  //        CCSpriteFrame *EYE_SURPRISE ;
  cocos2d::CCSpriteFrame *BLOCKS_GREEN_LAND_02;
  cocos2d::CCSpriteFrame *GARBAGE_TOP_BOTTOM;
  cocos2d::CCSpriteFrame *BLOCKS_GREEN_COMPRESSED_02;
  cocos2d::CCSpriteFrame *BLOCKS_PURPLE_PANIC_04;
  cocos2d::CCSpriteFrame *GARBAGE_LEFT;
  cocos2d::CCSpriteFrame *CURSOR_02;
  cocos2d::CCSpriteFrame *BLOCKS_PURPLE_HOVER_03;
  cocos2d::CCSpriteFrame *BLOCKS_YELLOW_COMPRESSED_03;
  cocos2d::CCSpriteFrame *BLOCKS_YELLOW_PANIC_04;
  cocos2d::CCSpriteFrame *GARBAGE_PLAIN;
  cocos2d::CCSpriteFrame *BLOCKS_RED_HOVER_01;
  cocos2d::CCSpriteFrame *BLOCKS_BLUE_COMPRESSED_04;
  cocos2d::CCSpriteFrame *BLOCKS_PURPLE_IDLE;
  cocos2d::CCSpriteFrame *BLOCKS_PURPLE_HOVER_04;
  cocos2d::CCSpriteFrame *BLOCKS_PURPLE_PANIC_02;
  cocos2d::CCSpriteFrame *BLOCKS_GREEN_COMPRESSED_03;
  cocos2d::CCSpriteFrame *BLOCKS_RED_IDLE;
  cocos2d::CCSpriteFrame *BLOCKS_YELLOW_HOVER_01;
  cocos2d::CCSpriteFrame *BLOCKS_PURPLE_LAND_01;
  cocos2d::CCSpriteFrame *BLOCKS_PURPLE_COMPRESSED_04;
  cocos2d::CCSpriteFrame *BLOCKS_YELLOW_COMPRESSED_01;
  cocos2d::CCSpriteFrame *BLOCKS_PURPLE_COMPRESSED_02;
  cocos2d::CCSpriteFrame *BLOCKS_RED_COMPRESSED_01;
  cocos2d::CCSpriteFrame *BLOCKS_RED_HOVER_02;
  cocos2d::CCSpriteFrame *GARBAGE_TOP_LEFT;
  cocos2d::CCSpriteFrame *BLOCKS_PURPLE_COMPRESSED_03;
  cocos2d::CCSpriteFrame *BLOCKS_RED_COMPRESSED_04;
  cocos2d::CCSpriteFrame *GARBAGE_TOP_LEFT_BOTTOM;
  cocos2d::CCSpriteFrame *BLOCKS_YELLOW_IDLE;
  cocos2d::CCSpriteFrame *BLOCKS_PURPLE_LAND_02;
  cocos2d::CCSpriteFrame *BLOCKS_PURPLE_HAPPY;
  cocos2d::CCSpriteFrame *BLOCKS_BLUE_COMPRESSED_03;
  cocos2d::CCSpriteFrame *BLOCKS_BLUE_HOVER_03;
  cocos2d::CCSpriteFrame *GARBAGE_RIGHT;
  cocos2d::CCSpriteFrame *BLOCKS_RED_PANIC_02;
  cocos2d::CCSpriteFrame *BLOCKS_GREEN_HAPPY;
  cocos2d::CCSpriteFrame *BLOCKS_GREEN_PANIC_02;
  cocos2d::CCSpriteFrame *BLOCKS_YELLOW_LAND_02;
  cocos2d::CCSpriteFrame *BLOCKS_BLUE_HOVER_02;
  cocos2d::CCSpriteFrame *BLOCKS_RED_HOVER_03;
  cocos2d::CCSpriteFrame *BLOCKS_GREEN_LAND_01;
  cocos2d::CCSpriteFrame *BLOCKS_BLUE_IDLE;
  cocos2d::CCSpriteFrame *BLOCKS_RED_HAPPY;
  cocos2d::CCSpriteFrame *BLOCKS_YELLOW_HOVER_04;
  cocos2d::CCSpriteFrame *GARBAGE_SINGLE;
  //        CCSpriteFrame *EYE ;
  cocos2d::CCSpriteFrame *BLOCKS_GREEN_PANIC_03;
  cocos2d::CCSpriteFrame *GARBAGE_LEFT_BOTTOM;
  cocos2d::CCSpriteFrame *BLOCKS_BLUE_PANIC_03;
  //  CCSpriteFrame *LOSE;
  cocos2d::CCSpriteFrame *BLOCKS_GREEN_HOVER_02;
  cocos2d::CCSpriteFrame *BLOCKS_YELLOW_PANIC_03;
  cocos2d::CCSpriteFrame *BLOCKS_PURPLE_FLASH;
  cocos2d::CCSpriteFrame *BLOCKS_BLUE_COMPRESSED_01;
  cocos2d::CCSpriteFrame *BLOCKS_GREEN_COMPRESSED_04;
  cocos2d::CCSpriteFrame *BLOCKS_RED_LAND_01;
  cocos2d::CCSpriteFrame *BLOCKS_YELLOW_COMPRESSED_04;
  cocos2d::CCSpriteFrame *BLOCKS_RED_COMPRESSED_03;
  cocos2d::CCSpriteFrame *GARBAGE_BOTTOM;
  cocos2d::CCSpriteFrame *BLOCKS_GREEN_PANIC_04;
  cocos2d::CCSpriteFrame *BLOCKS_RED_COMPRESSED_02;
  cocos2d::CCSpriteFrame *BLOCKS_BLUE_HOVER_04;
  cocos2d::CCSpriteFrame *BLOCKS_YELLOW_PANIC_01;
  cocos2d::CCSpriteFrame *BLOCKS_GREEN_HOVER_04;
  cocos2d::CCSpriteFrame *BLOCKS_GREEN_HOVER_01;
  cocos2d::CCSpriteFrame *BLOCKS_BLUE_LAND_02;
  cocos2d::CCSpriteFrame *BLOCKS_YELLOW_FLASH;
  cocos2d::CCSpriteFrame *BLOCKS_YELLOW_LAND_01;
  cocos2d::CCSpriteFrame *BLOCKS_PURPLE_COMPRESSED_01;
  cocos2d::CCSpriteFrame *GARBAGE_TOP_RIGHT;
  cocos2d::CCSpriteFrame *BLOCKS_GREEN_HOVER_03;
  cocos2d::CCSpriteFrame *BLOCKS_GREEN_PANIC_01;
  cocos2d::CCSpriteFrame *BLOCKS_YELLOW_COMPRESSED_02;
  cocos2d::CCSpriteFrame *BLOCKS_YELLOW_PANIC_02;
  cocos2d::CCSpriteFrame *BLOCKS_RED_FLASH;
  cocos2d::CCSpriteFrame *BLOCKS_PURPLE_PANIC_03;
  cocos2d::CCSpriteFrame *BLOCKS_PURPLE_HOVER_02;
  cocos2d::CCSpriteFrame *BLOCKS_BLUE_COMPRESSED_02;
  cocos2d::CCSpriteFrame *BLOCKS_BLUE_LAND_01;

  Animation *YELLOW_PANICKING;
  Animation *BLUE_PANICKING;
  Animation *RED_PANICKING;
  Animation *GREEN_PANICKING;
  Animation *PURPLE_PANICKING;

  Animation *YELLOW_COMPRESSING;
  Animation *BLUE_COMPRESSING;
  Animation *RED_COMPRESSING;
  Animation *GREEN_COMPRESSING;
  Animation *PURPLE_COMPRESSING;

  Animation *YELLOW_BLINKING;
  Animation *BLUE_BLINKING;
  Animation *RED_BLINKING;
  Animation *GREEN_BLINKING;
  Animation *PURPLE_BLINKING;
  Animation *GARBAGE_BLINKING;

  Animation *CURSOR;
};

#endif //__AbstractPanelScene_H_
