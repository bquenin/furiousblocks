//
// Created by bquenin on 10/8/12.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "StarNumber.h"

StarNumber::StarNumber(int32_t x, int32_t y, std::string label, ccColor3B color) {
  ccSprite = CCSprite::createWithSpriteFrameName("star.png");
  ccSprite->setPosition(ccp(x, y));
  ccSprite->setColor(color);
  ccLabel = CCLabelBMFont::create(label.c_str(), "coopblack32.fnt");
  ccLabel->setPosition(ccp(x, y));
}
