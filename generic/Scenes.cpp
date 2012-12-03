//
// Created by bquenin on 12/3/12.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "Scenes.h"

void Scenes::create() {
  logoScene = LogoScene::scene();
  panelScene = PanelScene::scene();
  titleScene= TitleScene::scene();
  tutorialScene = TutorialScene::scene();
}
