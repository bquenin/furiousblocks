//
// Created by bquenin on 11/2/12.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __TutorialScene_H_
#define __TutorialScene_H_

#include <iostream>
#include "AbstractPanelScene.h"
#include "FuriousBlocksCoreListener.h"
#include "BlockType.h"

class TutorialScene : public AbstractPanelScene, FuriousBlocksCoreListener {
private:
  Player *player;

  //  static constexpr BlockType empty[][6] = {
  //      {BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL}
  //  };

  static constexpr BlockType
  combo4and5[][6] = {
  {
    BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL
  }, //
  {
    BlockType::YELLOW, BlockType::RED, static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::RED, BlockType::YELLOW
  }, //
  {
    BlockType::YELLOW, BlockType::RED, static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::RED, BlockType::YELLOW
  }, //
  {
    BlockType::RED, BlockType::GREEN, static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::GREEN, BlockType::RED
  }, //
  {
    static_cast<BlockType>(-1), BlockType::RED, static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::RED, static_cast<BlockType>(-1)
  }, //
  {
    static_cast<BlockType>(-1), static_cast<BlockType>(-1), static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::RED, static_cast<BlockType>(-1)
  }
};

  //  static constexpr BlockType combo6and10[][6] = {
  //      {BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL}, //
  //      {BlockType::YELLOW, BlockType::RED, static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::RED, BlockType::YELLOW}, //
  //      {BlockType::RED, BlockType::YELLOW, static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::RED, BlockType::YELLOW}, //
  //      {BlockType::YELLOW, BlockType::RED, static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::YELLOW, BlockType::RED}, //
  //      {static_cast<BlockType>(-1), static_cast<BlockType>(-1), static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::RED, BlockType::YELLOW}, //
  //      {static_cast<BlockType>(-1), static_cast<BlockType>(-1), static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::RED, BlockType::YELLOW}
  //  };
  //
  //
  //  static constexpr BlockType chainx2[][6] = { //
  //      {BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL}, //
  //      {static_cast<BlockType>(-1), BlockType::GREEN, BlockType::RED, BlockType::RED, static_cast<BlockType>(-1), BlockType::RED}, //
  //      {static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::GREEN, BlockType::GREEN, static_cast<BlockType>(-1), static_cast<BlockType>(-1)}
  //  };
  //
  //  static constexpr BlockType chainx3[][6] = { //
  //      {BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL}, //
  //      {BlockType::PURPLE, BlockType::GREEN, BlockType::RED, BlockType::RED, static_cast<BlockType>(-1), BlockType::RED}, //
  //      {static_cast<BlockType>(-1), BlockType::PURPLE, BlockType::GREEN, BlockType::GREEN, static_cast<BlockType>(-1), static_cast<BlockType>(-1)}, //
  //      {static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::PURPLE, static_cast<BlockType>(-1), static_cast<BlockType>(-1), static_cast<BlockType>(-1)}
  //  };
  //
  //  static constexpr BlockType Etc4ChainsPanel[][6] = { //
  //      {BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL}, //
  //      {BlockType::BLUE, BlockType::BLUE, BlockType::RED, BlockType::RED, BlockType::YELLOW, BlockType::TUTORIAL}, //
  //      {BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::BLUE, BlockType::GREEN, BlockType::PURPLE, BlockType::PURPLE}, //
  //      {BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::YELLOW, BlockType::RED, BlockType::RED, BlockType::TUTORIAL}, //
  //      {BlockType::TUTORIAL, BlockType::BLUE, BlockType::PURPLE, BlockType::PURPLE, BlockType::YELLOW, BlockType::TUTORIAL}, //
  //      {BlockType::BLUE, BlockType::TUTORIAL, BlockType::YELLOW, BlockType::GREEN, BlockType::YELLOW, BlockType::TUTORIAL}, //
  //      {BlockType::TUTORIAL, BlockType::BLUE, BlockType::YELLOW, BlockType::GREEN, BlockType::RED, BlockType::TUTORIAL}, //
  //      {BlockType::TUTORIAL, BlockType::PURPLE, BlockType::RED, BlockType::PURPLE, BlockType::TUTORIAL, BlockType::TUTORIAL} //
  //  };

public:
  TutorialScene();
  bool init();
  void update(float d);
  void onCombo(Combo *combo);
  void onGameOver();
  //  void onBeginningTweenFinished(void);

  // there's no 'id' in cpp, so we recommend to return the exactly class pointer
  static cocos2d::CCScene *scene();

  // Implement the "static node()" method manually
  CREATE_FUNC(TutorialScene);
};

#endif //__TutorialScene_H_
