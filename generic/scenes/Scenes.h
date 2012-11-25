//
// Created by bquenin on 11/25/12.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __Scenes_H_
#define __Scenes_H_

#include <iostream>
#include "TutorialScene.h"
#include "TitleScene.h"


class Scenes {
public:
  CCScene *titleScene;
  CCScene *tutorialScene;

  Scenes();
};

#endif //__Scenes_H_
