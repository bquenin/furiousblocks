//
// Created by bquenin on 2/26/13.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __Leveler_H_
#define __Leveler_H_

#include <iostream>
#include "PanelHelper.h"


class Leveler {
public:
  Leveler(PanelHelper& helper);

  std::unique_ptr<fb::Point> compute();
  std::unique_ptr<fb::Point> findLowestEmptyBlock();

  PanelHelper& helper;
  const Panel& panel; /// Convenience reference
};


#endif //__Leveler_H_
