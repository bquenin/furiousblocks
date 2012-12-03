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

class QuitOverlay : public CCLayerColor {
private:
  CCControlButton *skipButton;
  CCScale9Sprite *skipBackgroundButton;
  CCScale9Sprite *skipBackgroundHighlightedButton;

  CCControlButton *resumeButton;
  CCScale9Sprite *resumeBackgroundButton;
  CCScale9Sprite *resumeBackgroundHighlightedButton;

public:
  QuitOverlay();
  bool init();
  void skipAction(CCObject *sender);
  void resumeAction(CCObject *sender);

  // Implement the "static node()" method manually
  CREATE_FUNC(QuitOverlay);
};

#endif //__QuitOverlay_H_
