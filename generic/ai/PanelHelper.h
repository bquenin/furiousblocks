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

  bool isBlockMoveableToPosition(const int start, const int end, const int row) const;
  bool doesRowContainBlockType(const int row, const BlockType blockType) const;

  std::unique_ptr<fb::Point> getClosestBlock(const int column, const int row) const;
  std::unique_ptr<fb::Point> getClosestBlockWithType(const int column, const int row, const BlockType type) const;

  const Panel &panel;

};


#endif //__PanelHelper_H_
