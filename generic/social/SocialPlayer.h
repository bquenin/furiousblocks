//
// Created by bquenin on 1/26/13.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __SocialPlayer_H_
#define __SocialPlayer_H_

#include <iostream>


class SocialPlayer {
public:
  uint64_t id;
  std::string firstName;
  std::string lastName;

  SocialPlayer(uint64_t id, const std::string& firstName, const std::string& lastName);
};

#endif //__SocialPlayer_H_
