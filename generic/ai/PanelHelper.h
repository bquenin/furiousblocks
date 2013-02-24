//
// Created by bquenin on 2/24/13.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __PanelHelper_H_
#define __PanelHelper_H_

#include <iostream>
#include "Panel.h"


class PanelHelper {
public:
  PanelHelper(const Panel &panel) : panel(panel) {};

  bool isBlockSwitchPossible(const fb::Point &location);

  const Panel &panel;
};


#endif //__PanelHelper_H_
