//
// Created by bquenin on 11/25/12.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __PanelMenuOverlay_H_
#define __PanelMenuOverlay_H_

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class PanelMenuOverlay : public CCLayerColor {
private:

  CCControlButton *continueButton;
  CCControlButton *restartButton;
  CCControlButton *endGameButton;

public:
  // Implement the "static node()" method manually
  CREATE_FUNC(PanelMenuOverlay);

  PanelMenuOverlay();
  bool init();
  void continueAction(CCObject *sender);
  void restartAction(CCObject *sender);
  void endGameAction(CCObject *sender);
  void valueChanged(CCObject *sender, CCControlEvent controlEvent);
};

#endif //__PanelMenuOverlay_H_
