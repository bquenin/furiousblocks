//
// Created by bquenin on 11/12/12.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __QuitOverlay_H_
#define __QuitOverlay_H_

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class QuitOverlay : public cocos2d::CCLayerColor {
private:
  CCControlButton *skipButton;
  CCControlButton *resumeButton;

public:
  QuitOverlay();
  bool init();
  void update(float dt);

  // Implement the "static node()" method manually
  CREATE_FUNC(QuitOverlay);
};

#endif //__QuitOverlay_H_
