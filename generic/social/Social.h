//
// Created by bquenin on 1/23/13.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __Social_H_
#define __Social_H_

#include <iostream>
#include <MacTypes.h>
#include <Poco/JSON/Object.h>
#include "SocialPlayer.h"

using namespace Poco;

class Social {
  public:
  static void facebookLogin();
  static void facebookLogout();
  static void registerPlayer();
  static void createOrUpdatePlayer(const std::string& facebookId, const std::string& firstName, const std::string& lastName, const std::string& accessToken);
};

#endif //__Social_H_
