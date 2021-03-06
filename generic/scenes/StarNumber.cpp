//
// Created by bquenin on 10/8/12.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include <functional>
#include "StarNumber.h"
#include "easing_linear.hpp"
#include "easing_quart.hpp"
#include "AbstractPanelScene.h"
#include "Assets.h"

using namespace std::placeholders;

StarNumber::StarNumber(AbstractPanelScene* panelScene, int32_t x, int32_t y, std::string label, ccColor3B color)
: panelScene(panelScene) {
  ccSprite = CCSprite::createWithSpriteFrameName("star.png");
  ccSprite->setPosition(ccp(x, y));
  ccSprite->setColor(color);
  ccLabel = CCLabelBMFont::create(label.c_str(), "coopblack32.fnt");
  ccLabel->setPosition(ccp(x, y));

  panelScene->batch->addChild(ccSprite);
  panelScene->addChild(ccLabel);

  tweener.insert(claw::tween::single_tweener(y, y + Assets::TILE_SIZE, 1, std::bind(&CCNode::setPositionY, ccSprite, _1), claw::tween::easing_quart::ease_out));
  tweener.insert(claw::tween::single_tweener(y, y + Assets::TILE_SIZE, 1, std::bind(&CCNode::setPositionY, ccLabel, _1), claw::tween::easing_quart::ease_out));
  tweener.on_finished(std::bind(&StarNumber::onTweenFinished, this));
  panelScene->tweeners.insert(tweener);
}

void StarNumber::onTweenFinished() {
  panelScene->batch->removeChild(ccSprite, true);
  panelScene->removeChild(ccLabel, true);
  delete this;
}
