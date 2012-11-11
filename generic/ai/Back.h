//
// Created by bquenin on 10/22/12.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __Anonymous_H_
#define __Anonymous_H_

#include <iostream>
#include "TweenEquation.h"


class Back : public TweenEquation {
public:
  virtual float compute(float t) = 0;
  class test : public TweenEquation {
    float compute(float t) {
      return 0;
    }
  };
};

#endif //__Anonymous_H_
