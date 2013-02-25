//
// Created by bquenin on 2/24/13.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __ComboStarter_H_
#define __ComboStarter_H_

#include <memory>
#include "PanelHelper.h"

class ComboStarter {
public:
  ComboStarter(PanelHelper& helper);

  std::unique_ptr<fb::Point> compute();
  std::unique_ptr<fb::Point> computeHorizontalStarter();
  std::unique_ptr<fb::Point> computeVerticalStarter();
  std::unique_ptr<fb::Point> getHorizontalComboPointOnLine(BlockType blockType, int line);

  PanelHelper& helper;
  const Panel& panel; /// Convenience reference
};

#endif //__ComboStarter_H_
