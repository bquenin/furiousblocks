//
// Created by bquenin on 12/2/12.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __Assets_H_
#define __Assets_H_

#include <iostream>
#include <unordered_map>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "Animation.h"
#include "core/Block.h"
#include "NonLoopingAnimation.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace CocosDenshion;

class Assets {
public:
  static std::string format(char const *fmt, ...);

  static const cocos2d::CCSize designResolutionSize;
  static constexpr float transitionDuration = 0.5f;
  static constexpr int32_t TILE_SIZE = 96;

  void load();

  CCSpriteFrame *getBlockFrame(fb::Block *blockSituation, int64_t tick, bool compressed, bool panicking);
  std::unordered_map<int32_t, NonLoopingAnimation *> animations;

  // Assets
  CCSpriteFrame *FLOGO;

  CCSpriteFrame *TITLE;

  CCSpriteFrame *BG_TOP;
  CCSpriteFrame *BG_MIDDLE;
  CCSpriteFrame *BG_BOTTOM;

  CCSpriteFrame *BLOCKS_RED_PANIC_01;
  CCSpriteFrame *BLOCKS_BLUE_HOVER_01;
  CCSpriteFrame *BLOCKS_GREEN_COMPRESSED_01;
  CCSpriteFrame *BLOCKS_BLUE_FLASH;
  CCSpriteFrame *GARBAGE_BLINK;
  CCSpriteFrame *BLOCKS_PURPLE_PANIC_01;
  CCSpriteFrame *BLOCKS_RED_LAND_02;
  CCSpriteFrame *BLOCKS_YELLOW_HAPPY;
  CCSpriteFrame *BLOCKS_RED_PANIC_03;
  CCSpriteFrame *BLOCKS_BLUE_HAPPY;
  CCSpriteFrame *BLOCKS_BLUE_PANIC_01;
  CCSpriteFrame *CURSOR_01;
  CCSpriteFrame *GARBAGE_TOP;
  CCSpriteFrame *CURSOR_03;
  CCSpriteFrame *BLOCKS_YELLOW_HOVER_03;
  CCSpriteFrame *BLOCKS_PURPLE_HOVER_01;
  CCSpriteFrame *BLOCKS_YELLOW_HOVER_02;
  CCSpriteFrame *BLOCKS_GREEN_IDLE;
  CCSpriteFrame *BLOCKS_BLUE_PANIC_02;
  CCSpriteFrame *BLOCKS_GREEN_FLASH;
  CCSpriteFrame *BLOCKS_RED_HOVER_04;
  CCSpriteFrame *BLOCKS_RED_PANIC_04;
  CCSpriteFrame *GARBAGE_RIGHT_BOTTOM;
  CCSpriteFrame *GARBAGE_TOP_RIGHT_BOTTOM;
  CCSpriteFrame *BLOCKS_BLUE_PANIC_04;
  CCSpriteFrame *BLOCKS_GREEN_LAND_02;
  CCSpriteFrame *GARBAGE_TOP_BOTTOM;
  CCSpriteFrame *BLOCKS_GREEN_COMPRESSED_02;
  CCSpriteFrame *BLOCKS_PURPLE_PANIC_04;
  CCSpriteFrame *GARBAGE_LEFT;
  CCSpriteFrame *CURSOR_02;
  CCSpriteFrame *BLOCKS_PURPLE_HOVER_03;
  CCSpriteFrame *BLOCKS_YELLOW_COMPRESSED_03;
  CCSpriteFrame *BLOCKS_YELLOW_PANIC_04;
  CCSpriteFrame *GARBAGE_PLAIN;
  CCSpriteFrame *BLOCKS_RED_HOVER_01;
  CCSpriteFrame *BLOCKS_BLUE_COMPRESSED_04;
  CCSpriteFrame *BLOCKS_PURPLE_IDLE;
  CCSpriteFrame *BLOCKS_PURPLE_HOVER_04;
  CCSpriteFrame *BLOCKS_PURPLE_PANIC_02;
  CCSpriteFrame *BLOCKS_GREEN_COMPRESSED_03;
  CCSpriteFrame *BLOCKS_RED_IDLE;
  CCSpriteFrame *BLOCKS_YELLOW_HOVER_01;
  CCSpriteFrame *BLOCKS_PURPLE_LAND_01;
  CCSpriteFrame *BLOCKS_PURPLE_COMPRESSED_04;
  CCSpriteFrame *BLOCKS_YELLOW_COMPRESSED_01;
  CCSpriteFrame *BLOCKS_PURPLE_COMPRESSED_02;
  CCSpriteFrame *BLOCKS_RED_COMPRESSED_01;
  CCSpriteFrame *BLOCKS_RED_HOVER_02;
  CCSpriteFrame *GARBAGE_TOP_LEFT;
  CCSpriteFrame *BLOCKS_PURPLE_COMPRESSED_03;
  CCSpriteFrame *BLOCKS_RED_COMPRESSED_04;
  CCSpriteFrame *GARBAGE_TOP_LEFT_BOTTOM;
  CCSpriteFrame *BLOCKS_YELLOW_IDLE;
  CCSpriteFrame *BLOCKS_PURPLE_LAND_02;
  CCSpriteFrame *BLOCKS_PURPLE_HAPPY;
  CCSpriteFrame *BLOCKS_BLUE_COMPRESSED_03;
  CCSpriteFrame *BLOCKS_BLUE_HOVER_03;
  CCSpriteFrame *GARBAGE_RIGHT;
  CCSpriteFrame *BLOCKS_RED_PANIC_02;
  CCSpriteFrame *BLOCKS_GREEN_HAPPY;
  CCSpriteFrame *BLOCKS_GREEN_PANIC_02;
  CCSpriteFrame *BLOCKS_YELLOW_LAND_02;
  CCSpriteFrame *BLOCKS_BLUE_HOVER_02;
  CCSpriteFrame *BLOCKS_RED_HOVER_03;
  CCSpriteFrame *BLOCKS_GREEN_LAND_01;
  CCSpriteFrame *BLOCKS_BLUE_IDLE;
  CCSpriteFrame *BLOCKS_RED_HAPPY;
  CCSpriteFrame *BLOCKS_YELLOW_HOVER_04;
  CCSpriteFrame *GARBAGE_SINGLE;
  CCSpriteFrame *BLOCKS_GREEN_PANIC_03;
  CCSpriteFrame *GARBAGE_LEFT_BOTTOM;
  CCSpriteFrame *BLOCKS_BLUE_PANIC_03;
  CCSpriteFrame *BLOCKS_GREEN_HOVER_02;
  CCSpriteFrame *BLOCKS_YELLOW_PANIC_03;
  CCSpriteFrame *BLOCKS_PURPLE_FLASH;
  CCSpriteFrame *BLOCKS_BLUE_COMPRESSED_01;
  CCSpriteFrame *BLOCKS_GREEN_COMPRESSED_04;
  CCSpriteFrame *BLOCKS_RED_LAND_01;
  CCSpriteFrame *BLOCKS_YELLOW_COMPRESSED_04;
  CCSpriteFrame *BLOCKS_RED_COMPRESSED_03;
  CCSpriteFrame *GARBAGE_BOTTOM;
  CCSpriteFrame *BLOCKS_GREEN_PANIC_04;
  CCSpriteFrame *BLOCKS_RED_COMPRESSED_02;
  CCSpriteFrame *BLOCKS_BLUE_HOVER_04;
  CCSpriteFrame *BLOCKS_YELLOW_PANIC_01;
  CCSpriteFrame *BLOCKS_GREEN_HOVER_04;
  CCSpriteFrame *BLOCKS_GREEN_HOVER_01;
  CCSpriteFrame *BLOCKS_BLUE_LAND_02;
  CCSpriteFrame *BLOCKS_YELLOW_FLASH;
  CCSpriteFrame *BLOCKS_YELLOW_LAND_01;
  CCSpriteFrame *BLOCKS_PURPLE_COMPRESSED_01;
  CCSpriteFrame *GARBAGE_TOP_RIGHT;
  CCSpriteFrame *BLOCKS_GREEN_HOVER_03;
  CCSpriteFrame *BLOCKS_GREEN_PANIC_01;
  CCSpriteFrame *BLOCKS_YELLOW_COMPRESSED_02;
  CCSpriteFrame *BLOCKS_YELLOW_PANIC_02;
  CCSpriteFrame *BLOCKS_RED_FLASH;
  CCSpriteFrame *BLOCKS_PURPLE_PANIC_03;
  CCSpriteFrame *BLOCKS_PURPLE_HOVER_02;
  CCSpriteFrame *BLOCKS_BLUE_COMPRESSED_02;
  CCSpriteFrame *BLOCKS_BLUE_LAND_01;

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

#endif //__Assets_H_
