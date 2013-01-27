//
// Created by bquenin on 1/23/13.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __Social_H_
#define __Social_H_

#include <iostream>

class Social {
  public:
  static void facebookLogin();
  static void facebookLogout();
  static void registerPlayer();
  static void createOrUpdatePlayer(const std::string& facebookId, const std::string& firstName, const std::string& lastName, const std::string& accessToken);
  static void submitScore(const std::string& facebookId, uint64_t score);
};

#endif //__Social_H_
