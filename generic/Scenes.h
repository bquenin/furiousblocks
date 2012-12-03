//
// Created by bquenin on 12/3/12.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __Scenes_H_
#define __Scenes_H_

#include <iostream>
#include "TutorialScene.h"
#include "LogoScene.h"
#include "PanelScene.h"
#include "TitleScene.h"


class Scenes {
public:
  void create();

  CCScene *logoScene;
  CCScene *panelScene;
  CCScene *titleScene;
  CCScene *tutorialScene;
};

#endif //__Scenes_H_
