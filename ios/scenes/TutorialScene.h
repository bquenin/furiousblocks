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
#include "Script.h"
#include "TextToType.h"
#include "TutorialPlayer.h"

class TutorialScene : public AbstractPanelScene, FuriousBlocksCoreListener {
private:
  Script script;
  TutorialPlayer *tutorialPlayer;
  TextToType textToType;
  cocos2d::CCLabelBMFont *textBox;

  const std::vector<const std::vector<BlockType>> empty = {
      {BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL}
  };

  const std::vector<const std::vector<BlockType>> combo4and5 = {
      {BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL},
      {BlockType::YELLOW, BlockType::RED, static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::RED, BlockType::YELLOW},
      {BlockType::YELLOW, BlockType::RED, static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::RED, BlockType::YELLOW},
      {BlockType::RED, BlockType::GREEN, static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::GREEN, BlockType::RED},
      {static_cast<BlockType>(-1), BlockType::RED, static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::RED, static_cast<BlockType>(-1)},
      {static_cast<BlockType>(-1), static_cast<BlockType>(-1), static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::RED, static_cast<BlockType>(-1)}
  };

  const std::vector<const std::vector<BlockType>> combo6and10 = {
      {BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL}, //
      {BlockType::YELLOW, BlockType::RED, static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::RED, BlockType::YELLOW}, //
      {BlockType::RED, BlockType::YELLOW, static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::RED, BlockType::YELLOW}, //
      {BlockType::YELLOW, BlockType::RED, static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::YELLOW, BlockType::RED}, //
      {static_cast<BlockType>(-1), static_cast<BlockType>(-1), static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::RED, BlockType::YELLOW}, //
      {static_cast<BlockType>(-1), static_cast<BlockType>(-1), static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::RED, BlockType::YELLOW}
  };

  const std::vector<const std::vector<BlockType>> chainx2 = { //
      {BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL}, //
      {static_cast<BlockType>(-1), BlockType::GREEN, BlockType::RED, BlockType::RED, static_cast<BlockType>(-1), BlockType::RED}, //
      {static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::GREEN, BlockType::GREEN, static_cast<BlockType>(-1), static_cast<BlockType>(-1)}
  };

  const std::vector<const std::vector<BlockType>> chainx3 = { //
      {BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL}, //
      {BlockType::PURPLE, BlockType::GREEN, BlockType::RED, BlockType::RED, static_cast<BlockType>(-1), BlockType::RED}, //
      {static_cast<BlockType>(-1), BlockType::PURPLE, BlockType::GREEN, BlockType::GREEN, static_cast<BlockType>(-1), static_cast<BlockType>(-1)}, //
      {static_cast<BlockType>(-1), static_cast<BlockType>(-1), BlockType::PURPLE, static_cast<BlockType>(-1), static_cast<BlockType>(-1), static_cast<BlockType>(-1)}
  };

  const std::vector<const std::vector<BlockType>> etc4ChainsPanel = { //
      {BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::TUTORIAL}, //
      {BlockType::BLUE, BlockType::BLUE, BlockType::RED, BlockType::RED, BlockType::YELLOW, BlockType::TUTORIAL}, //
      {BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::BLUE, BlockType::GREEN, BlockType::PURPLE, BlockType::PURPLE}, //
      {BlockType::TUTORIAL, BlockType::TUTORIAL, BlockType::YELLOW, BlockType::RED, BlockType::RED, BlockType::TUTORIAL}, //
      {BlockType::TUTORIAL, BlockType::BLUE, BlockType::PURPLE, BlockType::PURPLE, BlockType::YELLOW, BlockType::TUTORIAL}, //
      {BlockType::BLUE, BlockType::TUTORIAL, BlockType::YELLOW, BlockType::GREEN, BlockType::YELLOW, BlockType::TUTORIAL}, //
      {BlockType::TUTORIAL, BlockType::BLUE, BlockType::YELLOW, BlockType::GREEN, BlockType::RED, BlockType::TUTORIAL}, //
      {BlockType::TUTORIAL, BlockType::PURPLE, BlockType::RED, BlockType::PURPLE, BlockType::TUTORIAL, BlockType::TUTORIAL} //
  };

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
